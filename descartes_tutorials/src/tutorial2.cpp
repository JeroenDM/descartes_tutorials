// Core ros functionality like ros::init and spin
#include <ros/ros.h>
// ROS Trajectory Action server definition
#include <control_msgs/FollowJointTrajectoryAction.h>
// Means by which we communicate with above action-server
#include <actionlib/client/simple_action_client.h>

// Includes the descartes robot model we will be using
#include <descartes_moveit/ikfast_moveit_state_adapter.h>
// Includes the descartes trajectory type we will be using
#include <descartes_trajectory/axial_symmetric_pt.h>
#include <descartes_trajectory/cart_trajectory_pt.h>
// Includes the planner we will be using
#include <descartes_planner/dense_planner.h>

#include <tutorial_utilities/path_generation.h>
#include <tutorial_utilities/collision_object_utils.h>
//#include <tutorial_utilities/visualization.h>

typedef std::vector<descartes_core::TrajectoryPtPtr> TrajectoryVec;
typedef TrajectoryVec::const_iterator TrajectoryIter;

/**
 * Generates an completely defined (zero-tolerance) cartesian point from a pose
 */
descartes_core::TrajectoryPtPtr makeCartesianPoint(const Eigen::Affine3d& pose);
/**
 * Generates a cartesian point with free rotation about the Z axis of the EFF frame
 */
descartes_core::TrajectoryPtPtr makeTolerancedCartesianPoint(const Eigen::Affine3d& pose);

/**
 * Translates a descartes trajectory to a ROS joint trajectory
 */
trajectory_msgs::JointTrajectory
toROSJointTrajectory(const TrajectoryVec& trajectory, const descartes_core::RobotModel& model,
                     const std::vector<std::string>& joint_names, double time_delay);

/**
 * Sends a ROS trajectory to the robot controller
 */
bool executeTrajectory(const trajectory_msgs::JointTrajectory& trajectory);

bool waitForSubscribers(ros::Publisher & pub, ros::Duration timeout);

int main(int argc, char** argv)
{
  // Initialize ROS
  ros::init(argc, argv, "descartes_tutorial");
  ros::NodeHandle nh;

  // Required for communication with moveit components
  ros::AsyncSpinner spinner (1);
  spinner.start();

  // 0. Add objects to planning scene
  tutorial_utilities::testCollisionUtils();
    
  double objectX, objectY, objectZ, objectrX, objectrY, objectrZ;
  objectX = 1.0;
  objectY = 0.0;
  objectZ = 0.0;
  objectrX = 0.0;
  objectrY = 0.0;
  objectrZ = M_PI_2;
  Eigen::Affine3d objectpose;
  objectpose = descartes_core::utils::toFrame(objectX, objectY, objectZ, objectrX, objectrY, objectrZ, descartes_core::utils::EulerConventions::XYZ);

  moveit_msgs::PlanningScene planning_scene;
  Eigen::Vector3d objectscale(0.001,0.001,0.001);
  std::string workObjectID = "";
  if (!nh.getParam("/workObjectID", workObjectID))
  {
    ROS_WARN_STREAM("workObjectID parameter not found, using default: " << workObjectID);
  }
  std::string workObjectMeshPath = "";
  if (!nh.getParam("/workObjectPath", workObjectMeshPath))
  {
    ROS_WARN_STREAM("workObjectPath parameter not found, using default: " << workObjectMeshPath);
  }
  workObjectMeshPath = std::string("file://") + workObjectMeshPath;
  planning_scene.world.collision_objects.push_back(
    tutorial_utilities::makeCollisionObject(workObjectMeshPath, objectscale, workObjectID, objectpose)
  );
  planning_scene.object_colors.push_back(tutorial_utilities::makeObjectColor(workObjectID, 0.5, 0.5, 0.5, 1.0));

  ros::Publisher planning_scene_diff_publisher;
  planning_scene_diff_publisher = nh.advertise<moveit_msgs::PlanningScene>("planning_scene", 1);

  planning_scene.is_diff = true;

  ros::Rate loop_rate(10);
  ROS_INFO("Waiting for planning_scene subscriber.");
  if(waitForSubscribers(planning_scene_diff_publisher, ros::Duration(2.0)))
  {
	  planning_scene_diff_publisher.publish(planning_scene);
	  ros::spinOnce();
	  loop_rate.sleep();
    ROS_INFO("Object added to the world.");
  } else {
    ROS_ERROR("No subscribers connected, collision object not added");
  }

  // 1. Define sequence of points
  double x, y, z, rx, ry, rz;
  x = 1.0 - 0.025;
  y = 0.0;
  z = 0.008 + 0.025;
  rx = 0.0;
  ry = (M_PI / 2) + M_PI/4;
  rz = 0.0;
  TrajectoryVec points;
  int N_points = 30;

  std::vector<Eigen::Affine3d> poses;
  Eigen::Affine3d startPose;
  Eigen::Affine3d endPose;
  startPose = descartes_core::utils::toFrame(x, y, z, rx, ry, rz, descartes_core::utils::EulerConventions::XYZ);
  endPose = descartes_core::utils::toFrame(x, y + 0.4, z, rx, ry, rz, descartes_core::utils::EulerConventions::XYZ);
  poses = tutorial_utilities::line(startPose, endPose, N_points);

  for (unsigned int i = 0; i < N_points; ++i)
  {
    descartes_core::TrajectoryPtPtr pt = makeTolerancedCartesianPoint(poses[i]);
    points.push_back(pt);
  }

  // 2. Create a robot model and initialize it
  descartes_core::RobotModelPtr model (new descartes_moveit::IkFastMoveitStateAdapter);

  //Enable collision checking
  model->setCheckCollisions(true);

  // Name of description on parameter server. Typically just "robot_description".
  const std::string robot_description = "robot_description";

  // name of the kinematic group you defined when running MoveitSetupAssistant
  const std::string group_name = "manipulator";

  // Name of frame in which you are expressing poses. Typically "world_frame" or "base_link".
  const std::string world_frame = "base_link";

  // tool center point frame (name of link associated with tool)
  // this is also updated in the launch file of the robot
  const std::string tcp_frame = "tool_tip";

  if (!model->initialize(robot_description, group_name, world_frame, tcp_frame))
  {
    ROS_INFO("Could not initialize robot model");
    return -1;
  }

  // 3. Create a planner and initialize it with our robot model
  descartes_planner::DensePlanner planner;
  planner.initialize(model);

  // 4. Feed the trajectory to the planner
  if (!planner.planPath(points))
  {
    ROS_ERROR("Could not solve for a valid path");
    return -2;
  }

  TrajectoryVec result;
  if (!planner.getPath(result))
  {
    ROS_ERROR("Could not retrieve path");
    return -3;
  }

  // 5. Translate the result into a type that ROS understands
  // Get Joint Names
  std::vector<std::string> names;
  nh.getParam("controller_joint_names", names);
  // Generate a ROS joint trajectory with the result path, robot model, given joint names,
  // a certain time delta between each trajectory point
  trajectory_msgs::JointTrajectory joint_solution = toROSJointTrajectory(result, *model, names, 1.0);

  // 6. Send the ROS trajectory to the robot for execution
  if (!executeTrajectory(joint_solution))
  {
    ROS_ERROR("Could not execute trajectory!");
    return -4;
  }

  // Wait till user kills the process (Control-C)
  ROS_INFO("Done!");
  return 0;
}

descartes_core::TrajectoryPtPtr makeCartesianPoint(const Eigen::Affine3d& pose)
{
  using namespace descartes_core;
  using namespace descartes_trajectory;

  return TrajectoryPtPtr( new CartTrajectoryPt( TolerancedFrame(pose)) );
}

descartes_core::TrajectoryPtPtr makeTolerancedCartesianPoint(const Eigen::Affine3d& pose)
{
  using namespace descartes_core;
  using namespace descartes_trajectory;
  return TrajectoryPtPtr( new AxialSymmetricPt(pose, M_PI/2.0-0.0001, AxialSymmetricPt::Z_AXIS) );
}

trajectory_msgs::JointTrajectory
toROSJointTrajectory(const TrajectoryVec& trajectory,
                     const descartes_core::RobotModel& model,
                     const std::vector<std::string>& joint_names,
                     double time_delay)
{
  // Fill out information about our trajectory
  trajectory_msgs::JointTrajectory result;
  result.header.stamp = ros::Time::now();
  result.header.frame_id = "world_frame";
  result.joint_names = joint_names;

  // For keeping track of time-so-far in the trajectory
  double time_offset = 0.0;
  // Loop through the trajectory
  for (TrajectoryIter it = trajectory.begin(); it != trajectory.end(); ++it)
  {
    // Find nominal joint solution at this point
    std::vector<double> joints;
    it->get()->getNominalJointPose(std::vector<double>(), model, joints);

    // Fill out a ROS trajectory point
    trajectory_msgs::JointTrajectoryPoint pt;
    pt.positions = joints;
    // velocity, acceleration, and effort are given dummy values
    // we'll let the controller figure them out
    pt.velocities.resize(joints.size(), 0.0);
    pt.accelerations.resize(joints.size(), 0.0);
    pt.effort.resize(joints.size(), 0.0);
    // set the time into the trajectory
    pt.time_from_start = ros::Duration(time_offset);
    // increment time
    time_offset += time_delay;

    result.points.push_back(pt);
  }

  return result;
}

bool executeTrajectory(const trajectory_msgs::JointTrajectory& trajectory)
{
  // Create a Follow Joint Trajectory Action Client
  actionlib::SimpleActionClient<control_msgs::FollowJointTrajectoryAction> ac("joint_trajectory_action", true);
  if (!ac.waitForServer(ros::Duration(2.0)))
  {
    ROS_ERROR("Could not connect to action server");
    return false;
  }

  control_msgs::FollowJointTrajectoryGoal goal;
  goal.trajectory = trajectory;
  goal.goal_time_tolerance = ros::Duration(1.0);
  
  ac.sendGoal(goal);

  if (ac.waitForResult(goal.trajectory.points[goal.trajectory.points.size()-1].time_from_start + ros::Duration(5)))
  {
    ROS_INFO("Action server reported successful execution");
    return true;
  } else {
    ROS_WARN("Action server could not execute trajectory");
    return false;
  }
}

//Waits for a subscriber to subscribe to a publisher
bool waitForSubscribers(ros::Publisher & pub, ros::Duration timeout)
{
    if(pub.getNumSubscribers() > 0)
        return true;
    ros::Time start = ros::Time::now();
    ros::Rate waitTime(0.5);
    while(ros::Time::now() - start < timeout) {
        waitTime.sleep();
        if(pub.getNumSubscribers() > 0)
            break;
    }
    return pub.getNumSubscribers() > 0;
}