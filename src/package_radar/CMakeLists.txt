cmake_minimum_required(VERSION 3.8)
project(package_radar)

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(saed_interfaces REQUIRED)

add_executable(BatalhaNaval src/BatalhaNaval.cpp)
ament_target_dependencies(BatalhaNaval rclcpp saed_interfaces)

ament_package()