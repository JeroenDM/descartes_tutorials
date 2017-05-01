/*
 * Software License Agreement (Apache License)
 *
 * Copyright (c) 2016, Southwest Research Institute
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/*
 *  collision_object_utils.cpp
 *
 *  Created on: Feb 28, 2016
 *  Author: Bart and Jeroen
 */

#include <ros/ros.h>
#include </usr/include/eigen3/Eigen/Geometry>
#include <moveit_msgs/PlanningScene.h>
#include <moveit_msgs/CollisionObject.h>
#include <std_msgs/ColorRGBA.h>
#include <geometric_shapes/shape_operations.h>

namespace tutorial_utilities
{
    Eigen::Quaternion<double> eulerToQuat(double rotX, double rotY, double rotZ)
	{
		Eigen::Matrix3d m;
		m = Eigen::AngleAxisd(rotX, Eigen::Vector3d::UnitX())
			* Eigen::AngleAxisd(rotY, Eigen::Vector3d::UnitY())
			* Eigen::AngleAxisd(rotZ, Eigen::Vector3d::UnitZ());
	
		Eigen::AngleAxis<double> aa;
		aa = Eigen::AngleAxisd(m);
		
		Eigen::Quaternion<double> quat;
		quat = Eigen::Quaternion<double>(aa);

		return quat;
	}

    void testCollisionUtils()
    {
        ROS_INFO("============== Collision object utils library working !! ===============");
    }

    moveit_msgs::CollisionObject makeCollisionObject(std::string filepath, Eigen::Vector3d scale, std::string ID, Eigen::Affine3d pose)
    {
        moveit_msgs::CollisionObject co;

        //ROS_INFO("Loading mesh");
        shapes::Mesh* m = shapes::createMeshFromResource(filepath, scale);
        //ROS_INFO("Mesh loaded");

        shape_msgs::Mesh mesh;
        shapes::ShapeMsg mesh_msg;
        shapes::constructMsgFromShape(m, mesh_msg);
        mesh = boost::get<shape_msgs::Mesh>(mesh_msg);

        Eigen::Vector3d translations;
        translations = pose.translation();
        Eigen::Vector3d rotationsXYZ;
        rotationsXYZ = pose.rotation().eulerAngles(0,1,2);
        Eigen::Quaternion<double> quat;
        quat = eulerToQuat(rotationsXYZ[0], rotationsXYZ[1], rotationsXYZ[2]);

        co.header.frame_id = "base_link";
        co.id = ID;
        co.meshes.resize(1);
        co.mesh_poses.resize(1);
        co.meshes[0] = mesh;
        co.mesh_poses[0].position.x = translations[0];
        co.mesh_poses[0].position.y = translations[1];
        co.mesh_poses[0].position.z = translations[2];
        co.mesh_poses[0].orientation.w= quat.w();
        co.mesh_poses[0].orientation.x= quat.x();
        co.mesh_poses[0].orientation.y= quat.y();
        co.mesh_poses[0].orientation.z= quat.z();

        co.operation = co.ADD;

        return co;
    }

    std_msgs::ColorRGBA makeColor(double r, double g, double b, double a)
    {
        std_msgs::ColorRGBA color;
        color.r = r;
        color.g = g;
        color.b = b;
        color.a = a;
        return color;
    }

    moveit_msgs::ObjectColor makeObjectColor(std::string id, std_msgs::ColorRGBA color)
    {
        moveit_msgs::ObjectColor oc;
        oc.id = id;
        oc.color = color;
        return oc;
    }

    moveit_msgs::ObjectColor makeObjectColor(std::string id, double r, double g, double b, double a)
    {
        moveit_msgs::ObjectColor oc;
        oc.color = makeColor(r, g, b, a);
        oc.id = id;
        return oc;
    }

}