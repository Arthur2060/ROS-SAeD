cmake_minimum_required(VERSION 3.8)
project(modulo_radar)

# Declaracao de dependencias
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(saed_interfaces REQUIRED)

# Declaracao de executaveis (Segunda linha para especificar dependencias)
add_executable(batalha_naval src/BatalhaNaval.cpp)
ament_target_dependencies(batalha_naval rclcpp saed_interfaces)

# Instalacao das dependencias
install(TARGETS
  batalha_naval
  DESTINATION lib/${PROJECT_NAME})

ament_package()