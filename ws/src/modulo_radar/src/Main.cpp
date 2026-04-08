#include <functional>
#include <memory>
#include <stdio.h>
#include <sstream>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "CalculoDePonto.hpp"

class Main : public rclcpp::Node
{
public:
	Main() : Node("main")
	{
		auto topic_callback = [this](const saed_interfaces::msg::Radar &msg)
		{
			double distance = msg.distance;
			double angle = msg.angle;

			double X = calc.calcularDistanciaX(distance, angle);
			double Y = calc.calcularDistanciaY(distance, angle);

			RCLCPP_INFO(this->get_logger(), "Distance: %f, Angle: %f, X: %f, Y: %f", distance, angle, X, Y);
		};

		subscription_ = this->create_subscription<saed_interfaces::msg::Radar>(
			"topic", 10, topic_callback);
	}

	double getDistance()
	{
		return last_distance;
	}

	double getAngle()
	{
		return last_angle;
	}
}

private : CalculoDePonto calc;
}
;

int main(int argc, char *argv[])
{
	rclcpp::init(argc, argv);

	auto mainNode = std::make_shared<Main>();

	rclcpp::executors::MultiThreadedExecutor executor;

	executor.add_node(mainNode);
	executor.spin();

	rclcpp::shutdown();
	return 0;
}