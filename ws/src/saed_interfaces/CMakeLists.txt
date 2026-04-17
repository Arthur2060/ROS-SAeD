cmake_minimum_required(VERSION 3.8)
project(saed_interfaces)

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)

set(msg_files
  "msg/Radar.msg"
)

set(srv_files
  "srv/GetMapCell.srv"
  "srv/GetCellScale.srv"
)

rosidl_generate_interfaces(${PROJECT_NAME}
  ${msg_files}
  ${srv_files}
)

ament_export_dependencies(rosidl_default_runtime)
ament_package()
