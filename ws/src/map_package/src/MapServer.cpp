#include "MapManager.hpp"
#include "rclcpp/rclcpp.hpp"

class MapServer : rclcpp::Node 
{
    public:
        MapServer()
         : Node("map_server") 
        {

        }
    private:
};