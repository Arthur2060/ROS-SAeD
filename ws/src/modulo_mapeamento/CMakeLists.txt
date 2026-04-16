cmake_minimum_required(VERSION 3.8)
project(modulo_mapeamento)

# Declaracao de dependencias
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(saed_interfaces REQUIRED)

# Declaracao de executaveis (Segunda linha para especificar dependencias)
add_executable(modulo_mapeamento src/MapServer.cpp)
ament_target_dependencies(modulo_mapeamento rclcpp saed_interfaces)

# Instalacao das dependencias
install(TARGETS
  modulo_mapeamento
  DESTINATION lib/${PROJECT_NAME})

ament_package()