cmake_minimum_required(VERSION 2.8.3)
project(tutorial_utilities)

## Add support for C++11, supported in ROS Kinetic and newer
add_definitions(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  descartes_trajectory
)

catkin_package(
  INCLUDE_DIRS
    include
  LIBRARIES
    tutorial_utilities
  CATKIN_DEPENDS
    descartes_core
    descartes_trajectory
    trajectory_msgs
    moveit_msgs
    std_msgs
    moveit_ros_planning_interface
  DEPENDS
    eigen
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${Eigen_INCLUDE_DIRS}
)

add_library(tutorial_utilities
  src/path_generation.cpp
  src/collision_object_utils.cpp
  src/visualization.cpp
)

add_dependencies(tutorial_utilities
  ${catkin_EXPORTED_TARGETS}
)

#target_link_libraries(${PROJECT_NAME}
#  tutorial_utilities_lib
#  ${catkin_LIBRARIES}
#)

install(TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
)