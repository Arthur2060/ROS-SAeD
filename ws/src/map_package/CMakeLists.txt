cmake_minimum_required(VERSION 3.8)
project(map_package)

# Declaracao de dependencias
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(saed_interfaces REQUIRED)

# Declaracao de executaveis (Segunda linha para especificar dependencias)
add_executable(map src/MapServer.cpp)
ament_target_dependencies(map rclcpp saed_interfaces)

# Instalacao das dependencias
install(TARGETS
  map
  DESTINATION lib/${PROJECT_NAME})

ament_package()