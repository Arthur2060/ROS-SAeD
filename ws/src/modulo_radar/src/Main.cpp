#include <cmath>

#include <functional>
#include <memory>
#include <stdio.h>
#include <sstream>

#include "rclcpp/rclcpp.hpp"
#include "RadarSubscriber.cpp"
#include "CalculoDePonto.cpp"

int main(int argc, char * argv[]) {
	rclcpp::init(argc, argv);
  	
	CalculoDePonto calc;
    auto radarSubscriber = std::make_shared<RadarSubscriber>();

	distance = radarSubscriber.getDistance();
	angle = radarSubscriber.getAngle();

	X = calc.calcularDistanciaX(distance, angle);
	Y = calc.calcularDistanciaY(distance, angle);

	rclcpp::spin(radarSubscriber);
	rclcpp::shutdown();
	return 0;
}