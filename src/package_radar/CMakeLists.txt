cmake_minimum_required(VERSION 3.8)
project(package_radar)

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(saed_interfaces REQUIRED)

add_executable(batalha_naval src/BatalhaNaval.cpp)
ament_target_dependencies(batalha_naval rclcpp std_msgs saed_interfaces)

install(TARGETS
  batalha_naval
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()