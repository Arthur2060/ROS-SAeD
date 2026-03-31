#include "BatalhaNaval.cpp"

int main(int argc, char * argv[]) {
	rclcpp::init(argc, argv);
  	rclcpp::spin(
        std::make_shared<BatalhaNaval>()
    );
  	rclcpp::shutdown();
	return 0;
}