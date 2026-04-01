cmake_minimum_required(VERSION 3.8)
project(modulo_radar)

# Declaracao de dependencias
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(saed_interfaces REQUIRED)

# Declaracao de executaveis (Segunda linha para especificar dependencias)
add_executable(modulo_radar src/Main.cpp)
ament_target_dependencies(modulo_radar rclcpp)

add_executable(radar_subscriber src/RadarSubscriber.cpp)
ament_target_dependencies(radar_subscriber rclcpp saed_interfaces)

# Instalacao das dependencias
install(TARGETS
  modulo_radar
  radar_subscriber
  DESTINATION lib/${PROJECT_NAME})

ament_package()