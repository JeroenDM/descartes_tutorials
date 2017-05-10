# Descartes welding example
We implemented an example of path planning for a welding robot. We started from the tutorial1.cpp file and added new code and used a different robot. The original code is written [Bart's repository](https://github.com/Bart123456/lasrobot_ws). It was in serious need of cleaning and refactoring, therefore we started from scratch in this repository, which is a fork of the original code.

For our first contribution, we avoided changes things in the descartes core package. However, to include collision avoidance we had to make a small change to the moveit_state_adapter and the robot_model.

## What we want to show in the tutorial
- Visualization of a trajectory.
- Adding collision objects. (Should this be in a seperate cpp executable, same launch file?)
- To little trajectory points -> collision not detected (9 points for this example).
- (custom cost function)

**Important:** for the collision objects part, some lines of code are added in the descartes source code which can be found [here](https://github.com/JeroenDM/descartes/commits/welding_tutorial).
Originaly many of the parameters could be changed in the launch file. For simplicity this is left out in this tutorial at the moment.
    
 # Detailed planning of functions to add
 ## visualization
 - createMarker
 - createVisualFrame
 - addVisualFrame
 
 ## path_generation
 - line: generate a straight line of eigen poses all with the same orientation
 - circle: generate a circle of eigen poses around a fiven pose with a given radius
 
 ## collision_object_utils
 - createCollisionObject
 - createObjectColor
