# Descartes welding example

We implemented an example of path planning for a welding robot. The original code is written [Bart's repository](https://github.com/Bart123456/lasrobot_ws). It was in serious need of cleaning and refactoring, therefore we started from scratch in this repository, which is a fork of the original code.

Because I new to ROS development and open to suggestions, I will explain how I orginizade my workspace to write and test this tutorial. As IDE we use [RoboWare](http://www.roboware.me/), which is based on visual studio code.

## What we want to show in the tutorial

- Visualization of a trajectory.
- Adding collision objects.
- (custom cost function)

Reminders
- Function to convert eigen pose to orientation toleranced point.
- rviz config has to be adapted

## What we would like to improve

- Avoid big steps in task space.
- Solve RAM problem.
- Add tolerances in local tool frame.

## Workspace organization

Everything is in one (catkin) workspace, because using multiple workspaces caused problems. In the src folder of the workspaces I put all the git repos that containing the packages. This results in the following file structure:


descartes_ws/
  - build/
  - devel/
  - src/
    - [descartes/](https://github.com/JeroenDM/descartes/tree/indigo-devel)
      - ...
    - [descartes_tutorials/](https://github.com/JeroenDM/descartes_tutorials)
      - descartes_tutorials/
      - tutorial_utitilies/
        -include/
          - visualization.h
          - pose_generation.h
          - collision_object_utils.h
      - .gitignore
      - LICENSE
    - [kuka_kr120_robot/](https://github.com/JeroenDM/kuka_kr120_robot)
      - kuka_kr120_with_torch/
      - kuka_kr120_with_torch_ikfast/
      - kuka_kr120_with_torch_moveit_config/
    - [motoman_robot/](https://github.com/ros-industrial/motoman)
      - motoman_sia20d_support/
      - motoman_sia20d_moveit_config/
    - CMakeLists.txt
