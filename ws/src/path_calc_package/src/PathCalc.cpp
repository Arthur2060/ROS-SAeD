#include <cmath>
#include <vector>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class PathCalc : public rclcpp::Node
{
public:
    PathCalc() : Node("path_calc")
    {
        publisher_ = this->create_publisher<std_msgs::msg::String>("commands", 10);
    }

    PathCalc(int initialX, int initialY) : Node("path_calc")
    {
        this->currentPos[0] = initialX;
        this->currentPos[1] = initialY;

        publisher_ = this->create_publisher<std_msgs::msg::String>("commands", 10);
    }

    void setCurrentPosition(int x, int y)
    {
        currentPos[0] = x;
        currentPos[1] = y;
    }

    void setTargetPosition(int x, int y)
    {
        targetPos[0] = x;
        targetPos[1] = y;

        int distanceTargetCurrent[2] = {};

        distanceTargetCurrent[0] = targetPos[0] - currentPos[0];
        distanceTargetCurrent[1] = targetPos[1] - currentPos[1];

        std::vector<char> necessaryCommands;

        char verticalCommand;
        char horizontalCommand;

        horizontalCommand = (distanceTargetCurrent[0] >= 0) ? COMMANDS[4] : COMMANDS[2];

        verticalCommand = (distanceTargetCurrent[1] >= 0) ? COMMANDS[0] : COMMANDS[3];

        for (int counter = 0; counter <= distanceTargetCurrent[0]; counter++)
        {
            necessaryCommands.push_back(horizontalCommand);
        }

        for (int counter = 0; counter <= distanceTargetCurrent[1]; counter++)
        {
            necessaryCommands.push_back(verticalCommand);
        }

        publish_commands(necessaryCommands);
    }

private:
    int currentPos[2] = {};
    int targetPos[2] = {};
    const char COMMANDS[4] = {'W', 'A', 'S', 'D'};
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;

    void publish_commands(std::vector<char> commands) {
        std::string str(commands.begin(), commands.end());
        auto message = std_msgs::msg::String();
        message.data = str;
        this->publisher_->publish(message);
    }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<PathCalc>());
    rclcpp::shutdown();
}