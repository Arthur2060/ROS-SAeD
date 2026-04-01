#include <cmath>

#include <functional>
#include <memory>
#include <stdio.h>
#include <sstream>

#include "rclcpp/rclcpp.hpp"
#include "RadarSubscriber.cpp"

int main(int argc, char * argv[]) {
	rclcpp::init(argc, argv);
  	
    auto radarSubscriber = std::make_shared<RadarSubscriber>();

	distance = radarSubscriber.getDistance();
	angle = radarSubscriber.getAngle();

	rclcpp::spin(radarSubscriber);
	rclcpp::shutdown();
	return 0;
}