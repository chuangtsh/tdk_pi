FROM osrf/ros:humble-desktop

ARG USERNAME=user
ARG USER_UID=1000
ARG USER_GID=$USER_UID

RUN groupadd --gid $USER_GID $USERNAME \
    && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME \
    && apt-get update \
    && apt-get install -y sudo \
    && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME \
    && rm -rf /var/lib/apt/lists/*


# Install common tools
RUN apt-get update && apt-get install -y \
    curl \
    git \
    git-extras \
    htop \
    tree \
    net-tools \
    tmux \
    vim \
    wget \
    python3-pip \
    bash-completion

# Install ROS 2 Humble-specific packages not in humble-desktop
RUN apt-get update && apt-get install -y \
    ros-humble-dynamixel-sdk \
    ros-humble-turtlebot3-msgs \
    ros-humble-turtlebot3 \
    ros-humble-gazebo-ros-pkgs \
    ros-humble-rqt-tf-tree \
    ros-humble-rqt-plot \
    # foxglove
    ros-humble-rosbridge-server \
    ros-humble-foxglove-bridge
    # probably no use of groot in tdk

# System update and cleanup
RUN apt-get update && apt-get dist-upgrade -y \
    && apt-get autoremove -y \
    && apt-get autoclean -y \
    && rm -rf /var/lib/apt/lists/*

RUN echo "source /opt/ros/humble/setup.bash" >> /home/$USERNAME/.bashrc
RUN echo "source /usr/share/colcon_argcomplete/hook/colcon-argcomplete.bash" >> /home/$USERNAME/.bashrc

# Environment variables
ENV SHELL=/bin/bash
ENV TERM=xterm-256color

USER $USERNAME

# Default command )
CMD ["/bin/bash"]