# Workspace organization

Because we have to fix dependency issues and stuff, I put together an overview of the workspace layout I'm currently using for developing and testing the new tutorial.
Everything is in one (catkin) workspace, because using multiple workspaces caused problems. In the src folder of the workspaces I put all the git repos that containing the packages. This results in the following file structure:
With the provided links, it should be possible to recreate this workspace.

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
          - path_generation.h
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
    - [kuka_experimental](https://github.com/ros-industrial/kuka_experimental)
    - [industrial_core](https://github.com/ros-industrial/industrial_core)
    - CMakeLists.txt
