#!/bin/bash

# Variables
IMAGE_NAME="ros-noetic-foxy-bridge"
CONTAINER_NAME="ros-bridge-ws"
WORK_DIR="/home/user/ros_ws"
USERNAME=user

# Ensure X11 permissions
# echo "Setting X11 permissions..."
# xhost +local:docker || {
#     echo "Error: Failed to set xhost permissions."
#     exit 1
# }

# Set XAUTH_FILE to the path on host
# XAUTH_FILE=$XAUTHORITY

# Check if XAUTH_FILE exists
# if [ ! -f "$XAUTH_FILE" ]; then
#     echo "XAUTHORITY path not found."
#     echo "Generating .Xauthority..."
#     xauth generate "$DISPLAY" . || {
#         echo "Error: Failed to generate .Xauthority."
#         exit 1
#     }
#     XAUTH_FILE="$HOME/.Xauthority"
# fi

# Build the Docker image
echo "Building the Docker image..."
docker build -t $IMAGE_NAME --build-arg USERNAME=user .

# Remove any existing container with the same name
docker rm -f "$CONTAINER_NAME" 2>/dev/null || true

# Run the container
echo "Starting the container..."
docker run -d \
    --name "$CONTAINER_NAME" \
    --privileged \
    --network host \
    -e ROS_WS="$WORK_DIR" \
    -v /etc/timezone:/etc/timezone:ro \
    -v /etc/localtime:/etc/localtime:ro \
    -v /dev:/dev \
    -v "$(realpath ..):$WORK_DIR" \
    -it \
    "$IMAGE_NAME" \
    /bin/bash || {
        echo "Error: Failed to start container."
        docker logs "$CONTAINER_NAME"
        exit 1
    }


    # -v "$HOME/.Xauthority:/root/.Xauthority:ro" \
    # -e XAUTHORITY="/root/.Xauthority" \
    # -v /tmp/.X11-unix:/tmp/.X11-unix:rw \
    # -e DISPLAY="$DISPLAY" \
# Wait briefly to ensure the container is up
sleep 2

# Check if container is running
if ! docker ps | grep -q "$CONTAINER_NAME"; then
    echo "Error: Container is not running."
    docker logs "$CONTAINER_NAME"
    exit 1
fi

# Attach to an interactive shell
echo "Attaching to the container shell..."
docker exec -it "$CONTAINER_NAME" /bin/bash