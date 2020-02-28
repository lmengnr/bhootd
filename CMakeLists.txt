cmake_minimum_required(VERSION 3.6)

# The project name
project(bhoot)

add_subdirectory(thirdparty/catch)
add_subdirectory(thirdparty/paho.mqtt.c)
add_subdirectory(thirdparty/paho.mqtt.cpp)
add_subdirectory(src)
add_subdirectory(test)


