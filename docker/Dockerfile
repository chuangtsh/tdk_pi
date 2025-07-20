FROM --platform=linux/arm64 ubuntu:20.04 AS base

ARG USERNAME=user
ARG USER_UID=1000
ARG USER_GID=$USER_UID
ARG TARGETPLATFORM
ARG BUILDPLATFORM

SHELL ["/bin/bash", "-c"]

# Set non-interactive frontend for apt
ENV DEBIAN_FRONTEND=noninteractive

# Create user and group, set up sudo
RUN groupadd --gid $USER_GID $USERNAME \
    && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME \
    && apt-get update \
    && apt-get install -y sudo \
    && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME \
    && rm -rf /var/lib/apt/lists/*

# Install essential tools for ROS bridge
RUN apt-get update && apt-get install -y \
    curl \
    lsb-release \
    gnupg \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# Install ROS 1 Noetic (ARM64 compatible)
RUN sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list' \
    && curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | apt-key add - \
    && apt-get update \
    && apt-get install -y \
        ros-noetic-ros-base \
        ros-noetic-sensor-msgs \
        ros-noetic-geometry-msgs \
        ros-noetic-std-msgs \
    && rm -rf /var/lib/apt/lists/*

# Install ROS 2 Humble (excellent ARM64 support)
RUN curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg \
    && echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros2-latest.list \
    && apt-get update \
    && apt-get install -y \
        ros-humble-ros-base \
        ros-humble-ros1-bridge \
        python3-colcon-common-extensions \
        python3-rosdep \
    && rm -rf /var/lib/apt/lists/*

# System cleanup
RUN apt-get autoremove -y \
    && apt-get autoclean -y \
    && rm -rf /var/lib/apt/lists/*

FROM base AS release

# Environment variables
ENV SHELL=/bin/bash
ENV TERM=xterm-256color

# Copy and make script executable
COPY ./start-bridge.sh /start-bridge.sh
RUN chmod +x /start-bridge.sh

# Switch to user and setup environment
USER $USERNAME
RUN echo "source /opt/ros/noetic/setup.bash" >> ~/.bashrc \
    && echo "source /opt/ros/humble/setup.bash" >> ~/.bashrc

WORKDIR /
CMD ["./start-bridge.sh"]