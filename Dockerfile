FROM ros:jazzy AS base

# --- Instalações como root ---
RUN apt-get update && apt-get upgrade -y && \
    apt-get install -y \
      git \
      curl \
      python3-pip \
      python3-colcon-common-extensions \
      python3-rosdep \
      ros-jazzy-rosbridge-suite \
      ros-jazzy-rmw-cyclonedds-cpp \
    && rm -rf /var/lib/apt/lists/*

# Middleware estável em containers
ENV RMW_IMPLEMENTATION=rmw_cyclonedds_cpp

# --- Clonar repositório do projeto ---
WORKDIR /ros2_ws
RUN git clone https://github.com/Arthur2060/ROS-SAeD.git src/saed_ros

# --- Instalar micro-ROS agent ---
RUN git clone -b jazzy https://github.com/micro-ROS/micro_ros_setup.git \
      src/micro_ros_setup && \
    /bin/bash -c "\
      source /opt/ros/jazzy/setup.bash && \
      apt-get update && \
      rosdep update && \
      rosdep install --from-paths src --ignore-src -y && \
      colcon build --packages-select micro_ros_setup" && \
    /bin/bash -c "\
      source /opt/ros/jazzy/setup.bash && \
      source install/local_setup.bash && \
      ros2 run micro_ros_setup create_agent_ws.sh && \
      ros2 run micro_ros_setup build_agent.sh" && \
    rm -rf /var/lib/apt/lists/*

# --- Build do workspace completo ---
RUN /bin/bash -c "\
      source /opt/ros/jazzy/setup.bash && \
      source install/local_setup.bash && \
      colcon build --symlink-install"

# --- Usuário sem privilégios (após instalar tudo) ---
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

# --- Entrypoint: sobe tudo em paralelo ---
CMD ["/bin/bash", "-c", "\
  source /opt/ros/jazzy/setup.bash && \
  source /ros2_ws/install/local_setup.bash && \
  ros2 run micro_ros_agent micro_ros_agent udp4 --port 8888 & \
  ros2 launch saed_ros /ros2_ws/src/saed_ros/ws/launch/saed_ros_launch.xml & \
  ros2 launch rosbridge_server rosbridge_websocket_launch.xml && \
  wait"]