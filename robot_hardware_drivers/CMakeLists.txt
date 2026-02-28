cmake_minimum_required(VERSION 3.16)
project(my_package)

# Usar C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Encontrar dependências
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)

# Variáveis úteis
set(dependencies
  rclcpp
  std_msgs
  geometry_msgs
  sensor_msgs
)

# Incluir diretórios de headers
include_directories(include)

# Criar biblioteca (opcional)
add_library(${PROJECT_NAME}_lib
  src/utilities.cpp
)

target_link_libraries(${PROJECT_NAME}_lib
  ${dependencies}
)

ament_target_dependencies(${PROJECT_NAME}_lib
  ${dependencies}
)

# Criar executável principal
add_executable(${PROJECT_NAME}_node
  src/main.cpp
  src/node.cpp
)

target_link_libraries(${PROJECT_NAME}_node
  ${PROJECT_NAME}_lib
)

ament_target_dependencies(${PROJECT_NAME}_node
  ${dependencies}
)

# Instalar executáveis
install(TARGETS
  ${PROJECT_NAME}_node
  DESTINATION lib/${PROJECT_NAME}
)

# Instalar headers
install(DIRECTORY include/
  DESTINATION include
)

# Instalar launch files
install(DIRECTORY launch/
  DESTINATION share/${PROJECT_NAME}/launch
)

# Testes (opcional)
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_files()
endif()

# Exportar
ament_package()