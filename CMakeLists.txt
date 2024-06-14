cmake_minimum_required(VERSION 3.10)
project(XMOJ-Client)

add_subdirectory(Backend)
add_subdirectory(Frontend)

add_custom_target(XMOJ-Client DEPENDS XMOJ-Client-Backend XMOJ-Client-Frontend)