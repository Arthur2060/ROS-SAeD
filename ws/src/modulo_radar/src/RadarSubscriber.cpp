#include <functional>
#include <memory>
#include <stdio.h>
#include <sstream>

#include "rclcpp/rclcpp.hpp"
#include "saed_interfaces/msg/radar.hpp"
#include "CalculoDePonto.hpp"

CalculoDePonto calc;
const float DISTANCIA_DE_QUADRO = 0.3;

using std::placeholders::_1;

class RadarSubscriber : public rclcpp::Node
{
  private:
    rclcpp::Subscription<saed_interfaces::msg::Radar>::SharedPtr subscription_;

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

        float X = calc.calcularDistanciaX(last_distance, last_angle);
        float Y = calc.calcularDistanciaY(last_distance, last_angle);

        RCLCPP_INFO(this->get_logger(), "Calculado: X=%f, Y=%f", X / DISTANCIA_DE_QUADRO, Y / DISTANCIA_DE_QUADRO);
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
};

int main(int argc, char *argv[])
{

  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<RadarSubscriber>());
  rclcpp::shutdown();

  return 0;
}