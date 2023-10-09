# Lab 4: Simple Two-Dimensional Robot Control

## Overview

This simulator allows the user to build a very simple robot with common and rudimentary simulations using 2D sensors (LIDAR). This laboratory specifies the performance of a robot to be created in this two-dimensional simulation environment. The robot can perform obstacle detecion at the end of the lab.

### Lab 4 Link

Lab 4 Link: [Laboratory #4_20231002_cert-1.pdf](https://canvas.case.edu/courses/38747/assignments/509273)

## Basic Install

### STDR Simulator

First, the STDR simulator file must be downloaded to catkin_ws. Use the following command for ROS Noetic:

	git clone -b noetic-devel https://github.com/cwru-eecs-275/stdr_simulator.git
	
Comple after clone. I personally did not encounter any errors after first compilling.

### Install STDR Simulator Dependencies

The STDR Simulator has several dependencies that must be installed before the package can be built. Follow the commands below to achieve that.

#### -rosdep-

The rosdep utility installs dependencies declared in the package CMakeLists.txt and package.xml files. For ROS Noetic, copy the following commands:

	sudo apt install python3-rosdep
	
To initialize and update 'rosdep', use the following:

	sudo rosdep init   # Initialize rosdep
	rosdep update   # Update rosdep (notice that it does not include the use of sudo)	
	
Once 'rosdep' is prepared, it will install dependencies required to build the STDR Simulator. Use the following:

	cd ~/catkin_ws   # Get to the catkin workspace location
	rosdep install --from-paths src --ignore-src -r -y   # Install missing dependencies
	
All dependencies should now be installed to allow the STDR Simulator to be built. I also did not encounter any errors during this process.

#### -building STDR simulator-

It is now be possible to make the STDR Simulator. Use the following commands:

	source /opt/ros/noetic/setup.bash
	catkin_make
	source devel/setup.bash
	roslaunch stdr_launchers server_with_map_and_gui.launch 
	
This will launch the map with gui and the robot can be added later.

#### -installing STDR simulator-

Since the main ROS installation directories are protected, the sudo command is required to install the package. Use the following command to install the STDR simulator:

	sudo -- /bin/bash -c "source /opt/ros/noetic/setup.bash; catkin_make -DCMAKE_INSTALL_PREFIX=/opt/ros/noetic install"
	
#### -using STDR simulator-

To launch the STDR simulator with the map and gui, use the following command:

	source /opt/ros/noetic/setup.bash
	roslaunch stdr_simulators server_with_map_and_gui.launch
	
To create a robot, at the top of the window, click "Create robot". THen, in the popped up window, go to "Laser" and click the green plus sign. Then, at the bottom of the popped up window, click "Load robot to map". Use the cursor to select a point on the map and the robot will be added. 

### Teleoperate the Robot


