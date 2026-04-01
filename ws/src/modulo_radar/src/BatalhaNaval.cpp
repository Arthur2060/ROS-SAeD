#include <cmath>

#include <functional>
#include <memory>
#include <stdio.h>
#include <sstream>

#include "rclcpp/rclcpp.hpp"
#include "saed_interfaces/msg/radar.hpp"

using std::placeholders::_1;

class BatalhaNaval : public rclcpp::Node
{
public:
  BatalhaNaval()
  : Node("batalha_naval")
  {
    auto topic_callback = [this](const saed_interfaces::msg::Radar & msg){
		float distance = msg.distance;
		float angle = msg.angle;

		double X = calcularX(distance, angle);
		double Y = calcularY(distance, angle);

    };

    subscription_ = this->create_subscription<saed_interfaces::msg::Radar>(
      "topic", 10, topic_callback);
  }

private:
  	auto anguloEmRadi = [](float angle) {
		return angle * (M_PI / 180.0);
	};

	auto calcularX = [](float distance, float angle) {
		return sin(anguloEmRadi(angle)) * distance;
	};

	auto calcularY = [](float distance, float angle) {
		return cos(anguloEmRadi(angle)) * distance;
	};

  	rclcpp::Subscription<saed_interfaces::msg::Radar>::SharedPtr subscription_;
};