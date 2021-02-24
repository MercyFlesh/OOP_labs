cmake_minimum_required(VERSION 3.8)
project(OOP_lab_1 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDART 17)
set(CMAKE_BUILD_TYPE Debug)

file(GLOB SOURCES "*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

