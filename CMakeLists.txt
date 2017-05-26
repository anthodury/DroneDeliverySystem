cmake_minimum_required(VERSION 3.7)
project(DroneDeliverySystem)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")

set(SOURCE_FILES src/main.c include/Client.h include/Package.h include/Drone.h include/MotherShip.h include/Weather.h)
add_executable(DroneDeliverySystem ${SOURCE_FILES})