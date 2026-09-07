from setuptools import find_packages
from setuptools import setup

setup(
    name='move_to_point_action',
    version='0.0.0',
    packages=find_packages(
        include=('move_to_point_action', 'move_to_point_action.*')),
)
