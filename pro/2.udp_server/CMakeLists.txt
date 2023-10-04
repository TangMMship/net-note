cmake_minimum_required(VERSION 3.21)
project(udp_server C)
link_libraries(ws2_32)
set(CMAKE_C_STANDARD 99)

add_executable(udp_server main.c)
