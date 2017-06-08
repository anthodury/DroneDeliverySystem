cmake_minimum_required(VERSION 3.7)
project(DroneDeliverySystem)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread -W -Wall -ansi -pedantic")

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include/
)


set(SOURCE_FILES src/main.c src/Weather.c include/Client.h include/Package.h include/Drone.h include/MotherShip.h include/Weather.h src/Package.c src/Drone.c src/Client.c include/TrafficLanes.h src/TrafficLanes.c src/MotherShip.c)
add_executable(DroneDeliverySystem ${SOURCE_FILES})