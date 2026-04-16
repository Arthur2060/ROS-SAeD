FROM ros:jazzy AS base

# --- Instalações como root ---
RUN apt-get update && apt-get upgrade -y && \
    apt-get install -y \
      git \
      python3-colcon-common-extensions \
      ros-jazzy-rosbridge-suite \
      ros-jazzy-rmw-cyclonedds-cpp \
    && rm -rf /var/lib/apt/lists/*

# Middleware estável em containers
ENV RMW_IMPLEMENTATION=rmw_cyclonedds_cpp

WORKDIR /ros2_ws
RUN git clone https://github.com/Arthur2060/ROS-SAeD.git src/saed

# --- Build do workspace ---
RUN /bin/bash -c "source /opt/ros/jazzy/setup.bash && colcon build --symlink-install"

ARG UID=10001
RUN adduser \
    --disabled-password \
    --gecos "" \
    --home "/nonexistent" \
    --shell "/sbin/nologin" \
    --no-create-home \
    --uid "${UID}" \
    appuser

USER appuser

EXPOSE 9090

CMD ["/bin/bash", "-c", \
  "source /opt/ros/jazzy/setup.bash && \
   source /ros2_ws/install/setup.bash && \
   ros2 launch saed_ros saed_ros_launch.xml & \
   ros2 launch rosbridge_server rosbridge_websocket_launch.xml"]