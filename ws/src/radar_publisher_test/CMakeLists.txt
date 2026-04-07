cmake_minimum_required(VERSION 3.8)
project(radar_publisher_test)

# Declaracao de dependencias
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(saed_interfaces REQUIRED)

# Declaracao de executaveis (Segunda linha para especificar dependencias)
add_executable(radar_publisher_test src/main.cpp)
ament_target_dependencies(radar_publisher_test rclcpp saed_interfaces)

# Instalacao das dependencias
install(TARGETS
  radar_publisher_test
  DESTINATION lib/${PROJECT_NAME})

ament_package()