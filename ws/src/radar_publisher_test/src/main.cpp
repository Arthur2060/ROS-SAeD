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

                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> dist(0, 360);

                message.distance = dist(gen);
                message.angle = dist(gen);

                RCLCPP_INFO(this->get_logger(), "Publicando: ", std::to_string(message.distance), ", ", std::to_string(message.angle));

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