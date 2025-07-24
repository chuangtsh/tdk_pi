#!/bin/bash -e

if [ $# = 1 ]; then
    export ROS_MASTER_URI=$1
else
    export ROS_MASTER_URI=http://localhost:11311
fi

# Normally, sourcing the setup.bash file is sufficient to set up the ROS environment.
# However, the ros1_bridge package can't be found by ROS 2 even if we source the file. Manual sourcing is required.
source /opt/ros/noetic/setup.bash
source /opt/ros/foxy/setup.bash

# The ros1_bridge is installed via apt package, so it should be available after sourcing ROS 2
echo "ROS 1 and ROS 2 environments sourced successfully"

ros2 run ros1_bridge dynamic_bridge --bridge-all-topics