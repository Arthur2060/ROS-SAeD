cmake_minimum_required(VERSION 3.8)
project(modulo_radar)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/Radar.msg"
  "msg/AddPoint.srv"
)

add_executable(batalhaNaval src/batalhaNaval.cpp)
ament_target_dependencies(batalhaNaval rclcpp std_msgs)

add_executable(geradorDePontos src/geradorDePontos.cpp)
ament_target_dependencies(geradorDePontos rclcpp std_msgs)

install(TARGETS
  batalhaNaval
  geradorDePontos
  DESTINATION lib/${PROJECT_NAME})

ament_package()