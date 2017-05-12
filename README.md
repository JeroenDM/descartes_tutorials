# descartes_tutorials

## Introduction
In this fork of the descartes_tutorials repo, we are working on a second tutorial.
This tutorial will discuss: adding collision objects, visualizing trajectory points and why a planned path can still contain collisions.


(The instructions below will eventually also be added to [a tutorial on the ros wiki](http://wiki.ros.org/descartes/Tutorials/Robot%20Welding%20With%20Descartes).

## Installation

### Quickstart with existing workspace

### Longer explanation

I assume you have installed [ros indigo](http://wiki.ros.org/indigo), runnig on ubuntu 14.04.
Unfortunately this package cannot (yet) be installed just using apt-get.
Some of the packages are not realeased yet and have to be installed from source. If you don't have a github account, create a github account. (You can also download zip files, but using ros without github is like peper without salt.)

First, if you don't have a catkin workspace, you can [create one]http://wiki.ros.org/catkin/Tutorials/create_a_workspace) by executing the following commands in terminal:

Install catkin tools and rosdep used for building packages from source:

  sudo apt-get install python-catkin-tools python-rosdep
  
Now you can create the workspace (which is just a directory with some files in it).

  mkdir -p ~/catkin_ws/src
  cd ~/catkin_ws/src

and add the standard CMakeList.txt file in the src folder by running:

  catkin_init_workspace
  
In the src folder you can now add the packages you want to build. Is done by cloning the github repositories in the src folder, or downoad and unzip the repositories in this folder if you don't want to use a github account.

We start with a [modified version of descartes](https://github.com/JeroenDM/descartes) which adds the possiblity for collision detection with objects in the ros [indigo version of descartes](https://github.com/ros-industrial-consortium/descartes/tree/indigo-devel).
Stil in the souce directory, clone the package:

  git clone https://github.com/JeroenDM/descartes.git
  
The two other packages we want to add manually are [kuka_experimental](https://github.com/ros-industrial/kuka_experimental) for some cad files of robots and of course [descartes_tutorials](https://github.com/JeroenDM/descartes_tutorials) for the tutorial itself.

  git clone https://github.com/ros-industrial/kuka_experimental.git
  git clone https://github.com/JeroenDM/descartes_tutorials.git
  
Now we have all the necessary files for these packages, we can build them. This is done in the workspace root directory `~/catkin_ws`. Catkin will look in the `src` directory for packages to build.
 
  cd ~/catkin_ws
  
Before we can build, however, ros has to check whether we need some other packages on which these one depend. (Spoiler alert, they depend on a lot of other stuff.) For this purpose we do:

  rosdep install -r -y --from-paths src --ignore-src
  
 Options `-y` stands for answer yes to all, `r` for continue installing despite errors and the remaining stuff for where to ook and so on. More details [here](http://docs.ros.org/independent/api/rosdep/html/commands.html). If something goes wrong here, running `apt-get update` and then trying again can be a solution. If it worked, we can build the packages!
  
  catkin_make
  
Et voilà, you succesfully installed packages from source. Or noting is working and you almost threw you computer out of the window, in which case I would suggest hanging on to that computer and [create an issue](https://help.github.com/articles/creating-an-issue/).

Now before you can launch the tutorial, you have to source a setup file in your terminal, so ros knows where to look for the custom build packages. This file was automaticly created by the `catkin_make` command in the devel directory.

  source devel/setup.bash
  
Now the instructions in the paragraph below should work.

## How to launch?

We added two new launch files, "kuka_sim.launc" and "tutorial2.launch".
The first will launch the robot model in rviz for this tutorial.
The second will execute the tutorial source code.
