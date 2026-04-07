import asyncio
import rclpy
import RadarPublisher

from websockets.asyncio.server import serve
from rclpy.node import Node

async def echo(websocket):
    async for message in websocket:
        await websocket.send(message)

async def main(args=None):
    rclpy.init(args=args)
    
    radarPublisher = RadarPublisher()
    
    rclpy.spin(radarPublisher)
    radarPublisher.destroy_node()
    rclpy.shutdown()

    async with serve(echo, "localhost", 8765) as server:
        await server.serve_forever()

if __name__ == "__main__" :
    serve.run(main())