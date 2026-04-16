FROM ros:jazzy as base

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

ADD "https://github.com/Arthur2060/ROS-SAeD.git" /~

WORKDIR /ROS-SAeD

RUN sudo apt update && sudo apt upgrade -y

RUN cd ROS-SAeD && colcon build
RUN . install/setup.bash
WORKDIR ~/ROS_SAeD/ws/launch

EXPOSE 9090

CMD ros2 launch saed-ros