#include <functional>
#include <memory>
#include <stdio.h>
#include <sstream>

#include "rclcpp/rclcpp.hpp"
#include "saed_interfaces/msg/radar.hpp"

using std::placeholders::_1;

class RadarSubscriber : public rclcpp::Node
{
public:

  double last_distance;
  double last_angle;

  RadarSubscriber()
  : Node("radar_subscriber")
  {
	  auto topic_callback = [this](const saed_interfaces::msg::Radar &msg)
	  {
		  last_distance = msg.distance;
		  last_angle = msg.angle;
	  };

	  subscription_ = this->create_subscription<saed_interfaces::msg::Radar>(
		  "topic", 10, topic_callback);
  }

  double getDistance() {
	return last_distance;
  }

  double getAngle() {
	return last_angle;
  }

private:

  	rclcpp::Subscription<saed_interfaces::msg::Radar>::SharedPtr subscription_;
};