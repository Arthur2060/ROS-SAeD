#include <cmath>
#include <vector>
#include "rclcpp/rclcpp.hpp"

class PathCalc : public rclcpp::Node {
    public:
        PathCalc() : Node("path_calc") {}

        PathCalc(int initialX, int initialY) : Node("path_calc")
        {
            this->currentPos[0] = initialX;
            this->currentPos[1] = initialY;
        }

        void setCurrentPosition(int x, int y) {
            currentPos[0] = x;
            currentPos[1] = y;
        }

        void setTargetPosition(int x, int y) {
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
        }

    private:
        int currentPos[2] = {};
        int targetPos[2] = {};
        const char COMMANDS[4] = {'W', 'A', 'S', 'D'};
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<PathCalc>());
    rclcpp::shutdown();
}