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
	auto anguloEmRadi = [](float angle) {
		return angle * (M_PI / 180.0);
	};

	double calcularX(float distance, float angle) {
		return sin(anguloEmRadi(angle)) * distance;
	}

	double calcularY(float distance, float angle) {
		return cos(anguloEmRadi(angle)) * distance;
	}

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
  rclcpp::Subscription<saed_interfaces::msg::Radar>::SharedPtr subscription_;
};