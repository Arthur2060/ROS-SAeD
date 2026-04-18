cmake_minimum_required(VERSION 3.8)
project(path_calc_package)
# Declaracao de dependencias
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

# Declaracao de executaveis (Segunda linha para especificar dependencias)
add_executable(path_calc src/PathCalc.cpp)
ament_target_dependencies(path_calc rclcpp std_msgs)

# Instalacao das dependencias
install(TARGETS
  path_calc
  DESTINATION lib/${PROJECT_NAME})

ament_package()