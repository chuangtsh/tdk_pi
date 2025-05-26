FROM ubuntu:20.04

ARG USERNAME=user
ARG USER_UID=1000
ARG USER_GID=$USER_UID

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

# Install common tools
RUN apt-get update && apt-get install -y \
    curl \
    git \
    htop \
    tree \
    net-tools \
    tmux \
    vim \
    wget \
    python3-pip \
    bash-completion \
    lsb-release \
    gnupg \
    && rm -rf /var/lib/apt/lists/*

# Install ROS 1 Noetic
RUN sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list' \
    && curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | apt-key add - \
    && apt-get update \
    && apt-get install -y \
        ros-noetic-ros-base \
    && rm -rf /var/lib/apt/lists/*

# Install ROS 2 Foxy
RUN curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg \
    && echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros2-latest.list \
    && apt-get update \
    && apt-get install -y \
        ros-foxy-ros-base \
        ros-foxy-ros1-bridge \
        python3-colcon-common-extensions \
    && rm -rf /var/lib/apt/lists/*

# System update and cleanup
RUN apt-get update && apt-get dist-upgrade -y \
    && apt-get autoremove -y \
    && apt-get autoclean -y \
    && rm -rf /var/lib/apt/lists/*

RUN echo "source /usr/share/colcon_argcomplete/hook/colcon-argcomplete.bash" >> /home/$USERNAME/.bashrc

# Environment variables
ENV SHELL=/bin/bash
ENV TERM=xterm-256color

USER $USERNAME

# Default command
CMD ["/bin/bash"]