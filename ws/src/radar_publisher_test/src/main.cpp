#include <memory>
#include <chrono>
#include <memory>
#include <string>
#include <random>

#include "rclcpp/rclcpp.hpp"
#include "saed_interfaces/msg/radar.hpp"

using namespace std::chrono_literals;

class RadarPublisherTest : public rclcpp::Node {
    public:
        RadarPublisherTest() : Node("radar_publisher_test"), count_(0) {
            publisher_ = this->create_publisher<saed_interfaces::msg::Radar>("topic", 10);
            auto timer_callback = [this]() -> void
            {
                auto message = saed_interfaces::msg::Radar();

                message.distance = 2;
                message.angle = 90.0;

                RCLCPP_INFO(this->get_logger(), "Publicando: %.2fm, %.2f Graus", message.distance, message.angle);

                this->publisher_->publish(message);

                message.distance = 1;
                message.angle = 45.0;

                RCLCPP_INFO(this->get_logger(), "Publicando: %.2fm, %.2f Graus", message.distance, message.angle);

                this->publisher_->publish(message);

                message.distance = 2.5;
                message.angle = 65.0;

                RCLCPP_INFO(this->get_logger(), "Publicando: %.2fm, %.2f Graus", message.distance, message.angle);

                this->publisher_->publish(message);
            };
            timer_ = this->create_wall_timer(500ms, timer_callback);
        }
    private:
        rclcpp::TimerBase::SharedPtr timer_;
        rclcpp::Publisher<saed_interfaces::msg::Radar>::SharedPtr publisher_;
        size_t count_;
};

int main(int argc, char * argv[]) {

    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<RadarPublisherTest>());
    rclcpp::shutdown();

    return 0;
}