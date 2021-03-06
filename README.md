# descartes_tutorials

## Introduction
In this fork of the descartes_tutorials repo, we are working on a second tutorial.
This tutorial will discuss: adding collision objects, visualizing trajectory points and why a planned path can still contain collisions.


The instructions below are also written in [a tutorial on the ros wiki](http://wiki.ros.org/descartes/Tutorials/Robot%20Welding%20With%20Descartes).

In an aditional branch, [new_cost_function](https://github.com/JeroenDM/descartes_tutorials/tree/new_cost_function), the use of an alternative cost function for the graph search is demonstrated. It is important to notice that also for the [modified descartes package](https://github.com/JeroenDM/descartes), the branch has to be changed to [new_cost_function](https://github.com/JeroenDM/descartes/tree/new_cost_function).

## Installation

### Quickstart with existing workspace

In your workspace src folder, add three repositories.
```
  cd ~/catkin_ws/src
  git clone https://github.com/JeroenDM/descartes.git
  git clone https://github.com/ros-industrial/kuka_experimental.git
  git clone https://github.com/JeroenDM/descartes_tutorials.git
``` 

Now go to the workspace root folder, update dependencies, build the new packages and source them.
```
  cd ~/catkin_ws
  rosdep install -r -y --from-paths src --ignore-src
  catkin_make
  source devel/setup.bash
```

Now you should be able to launch the tutorial files "kuka_sim.launch" and "tutorial2.launch" in the following folder:
```
catkin_ws/src/descartes_tutorials/descartes_tutorials/launch
```
To be able to run the simulation you have to open a first command terminal (don't forget to source the workspace by running `source devel/setup.bash`) and run the "kuka_sim.launch" file.

```
  roslaunch descartes_tutorials kuka_sim.launch
```

Then, in a second terminal while leaving the first one running, launch "tutorial2.launch". (Don't forget to source the workspace again, as shown in the first line below.)

```
  source devel/setup.bash
  roslaunch descartes_tutorials tutorial2.launch
```

### Longer explanation

I assume you have installed [ros indigo](http://wiki.ros.org/indigo), runnig on ubuntu 14.04 LTS.
Unfortunately this package cannot (yet) be installed just using apt-get.
Some of the packages are not realeased and have to be installed from source. If you don't have a github account, create a github account. (You can also download zip files, but using ros without github is like peper without salt.)

First, if you don't have a catkin workspace, you can [create one]http://wiki.ros.org/catkin/Tutorials/create_a_workspace) by executing the commands in the grey boxes in the terminal.

Install catkin tools and rosdep used for building packages from source.
```
  sudo apt-get install python-catkin-tools python-rosdep
```
Now you can create the workspace (which is just a directory with some files in it).
```
  mkdir -p ~/catkin_ws/src
  cd ~/catkin_ws/src
```
and add the standard CMakeList.txt file in the src folder by running:
```
  catkin_init_workspace
```
In the src folder you can now add the packages you want to build by done by cloning the github repositories in the src folder. Or downoad and unzip the repositories in this folder if you don't want to use a github account.

We start with a [modified version of descartes](https://github.com/JeroenDM/descartes) which adds the possiblity for collision detection with objects other than the robot itself, nog present in the [indigo version of descartes](https://github.com/ros-industrial-consortium/descartes/tree/indigo-devel).
Stil in the `~catkin_ws/src` directory, clone the package.
```
  git clone https://github.com/JeroenDM/descartes.git
```  
The two other packages we want to add manually are [kuka_experimental](https://github.com/ros-industrial/kuka_experimental) for some cad files of robots and of course [descartes_tutorials](https://github.com/JeroenDM/descartes_tutorials) for the tutorial itself.
```
  git clone https://github.com/ros-industrial/kuka_experimental.git
  git clone https://github.com/JeroenDM/descartes_tutorials.git
```  
Now we have all the necessary files for these packages, we can build them. This is done in the workspace root directory `~/catkin_ws`. Catkin will look in the `src` directory for packages to build.
``` 
  cd ~/catkin_ws
```  
Before we can build, however, ros has to check whether we need some other packages on which these one depend. (Spoiler alert, they depend on a lot of other stuff.) For this purpose we do:
```
  rosdep install -r -y --from-paths src --ignore-src
```  
Options `-y` stands for answer yes to all, `r` for continue installing despite errors and the remaining stuff for where to look and so on. More details [here](http://docs.ros.org/independent/api/rosdep/html/commands.html). If something goes wrong here, running `apt-get update` and then trying again can be a solution. If it worked, we can build the packages!
```  
  catkin_make
```  
Et voilà, you succesfully installed packages from source....or noting is working and you almost threw you computer out of the window. In that case I would suggest hanging on to that computer and [creating an issue](https://help.github.com/articles/creating-an-issue/).

Now before you can launch the tutorial, you have to source a setup file in your terminal, so ros knows where to look for the custom build packages. This file was automaticly created by the `catkin_make` command in the devel directory.
```
  source devel/setup.bash
```  
Now the instructions in the paragraph below should work.

## How to launch?

We added two new launch files, "kuka_sim.launc" and "tutorial2.launch".
The first will launch the robot model in rviz for this tutorial.
The second will execute the tutorial source code.

Open a first command terminal (don't forget to source the workspace by running `source devel/setup.bash`) and run the "kuka_sim.launch" file.

```
  roslaunch descartes_tutorials kuka_sim.launch
```

Then, in a second terminal while leaving the first one running, launch "tutorial2.launch". (Don't forget to source the workspace again, as shown in the first line below.)

```
  source devel/setup.bash
  roslaunch descartes_tutorials tutorial2.launch
```
