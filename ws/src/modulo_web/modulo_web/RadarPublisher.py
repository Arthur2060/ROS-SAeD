import rclpy
from rclpy.node import Node

from saed_interfaces.msg import Radar

class RadarPublisher(Node):

    def __init__(self):
        super().__init__("RadarPublisher")
        self.publisher_ = self.create_publisher(Radar, "Radar", 10)
        timer_period = 0.5
        self.timer = self.create_timer(timer_period, self.timer_calback)
        self.distance = 0
        self.angle = 0
    
    def timer_calback(self):
        msg = Radar()
        msg.distance = self.distance
        msg.angle = self.angle
        self.publisher_.publish(msg)