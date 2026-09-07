import os
from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():

    return LaunchDescription([
        # Графический интерфейс
        Node(
            package="gui_control",
            executable="gui_control",
            name="gui_node"
        ),
        # Узел сервера действия
        Node(
            package="move_to_point_server",
            executable="move_to_point_server_node",
            name="move_to_point_server_node"
        ),
        # Запуск черепахи
        Node(
            package="turtlesim",
            executable="turtlesim_node",
            name="turtlesim_node"
        )
    ])
