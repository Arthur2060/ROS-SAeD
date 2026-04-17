#include "MapManager.hpp"
#include "rclcpp/rclcpp.hpp"
#include <memory>

#include "saed_interfaces/srv/get_cell_scale.hpp"
#include "saed_interfaces/srv/get_map_cell.hpp"

MapManager map(0.3, 10);

void getCellScale(
    const std::shared_ptr<saed_interfaces::srv::GetCellScale::Request> request,
    std::shared_ptr<saed_interfaces::srv::GetCellScale::Response> response)
{
    response->response = map.getCellDistance();
}

void getMapCell(
    const std::shared_ptr<saed_interfaces::srv::GetMapCell::Request> request,
    std::shared_ptr<saed_interfaces::srv::GetMapCell::Response> response)
{
    int x = request->x;
    int y = request->y;

    cell cell = map.getOneCell(x, y);

    response->x = cell.x;
    response->y = cell.y;
    response->value = cell.value;
}

int main(int argc, char **argv)
{

    rclcpp::init(argc, argv);
    std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("map_server");

    rclcpp::Service<saed_interfaces::srv::GetCellScale>::SharedPtr service =
        node->create_service<saed_interfaces::srv::GetCellScale>("get_cell_scale", &getCellScale);

    rclcpp::spin(node);
    rclcpp::shutdown();
    return 1;
}