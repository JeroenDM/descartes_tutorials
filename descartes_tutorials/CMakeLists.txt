cmake_minimum_required(VERSION 2.8.3)
project(descartes_tutorials)

find_package(catkin REQUIRED COMPONENTS
  descartes_core
  descartes_moveit
  descartes_trajectory
  descartes_planner
  tutorial_utilities REQUIRED
  trajectory_msgs
  moveit_ros_planning_interface
)

catkin_package()

###########
## Build ##
###########
include_directories(
  ${catkin_INCLUDE_DIRS}
  ${tutorial_utilities_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME}_tutorial1 src/tutorial1.cpp)
add_executable(${PROJECT_NAME}_tutorial2 src/tutorial2.cpp)

target_link_libraries(${PROJECT_NAME}_tutorial1
  ${catkin_LIBRARIES}
)
target_link_libraries(${PROJECT_NAME}_tutorial2
  ${catkin_LIBRARIES}
)

set_target_properties(${PROJECT_NAME}_tutorial1
  PROPERTIES OUTPUT_NAME tutorial1
  PREFIX "")
set_target_properties(${PROJECT_NAME}_tutorial2
  PROPERTIES OUTPUT_NAME tutorial2
  PREFIX "")


#############
## Install ##
#############

install(TARGETS ${PROJECT_NAME}_tutorial1
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(TARGETS ${PROJECT_NAME}_tutorial2
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
)
