# Descartes welding example

We implemented an example of path planning for a welding robot.

Because I new to ROS development an open to suggestions, I will explain how I orginizade my workspace to write and test this tutorial.

Everyting is in one (catkin) workspace, because using multiple workspaces caused problems. In the src folder of the workspaces I put all the git repos that containing the packages. This results in the following file structure:


descartes_ws/
  - build/
  - devel/
  - src/
    - descartes/
      - ...
    - descartes_tutorials/
      - descartes_tutorials/
      - .gitignore
      - LICENSE
    - [kuka_kr120_robot/](https://github.com/JeroenDM/kuka_kr120_robot)
      - kuka_kr120_with_torch/
      - kuka_kr120_with_torch_ikfast/
      - kuka_kr120_with_torch_moveit_config/
    - motoman_robot/
      - motoman_sia20d_support/
      - motoman_sia20d_moveit_config/
    - CMakeLists.txt
