cmake_minimum_required(VERSION 3.7)
project(untitled)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES GameProject/Direction.h GameProject/main.cpp GameProject/Utils.cpp GameProject/Utils.h GameProject/Snake.cpp GameProject/Snake.h GameProject/Point.cpp GameProject/Point.h GameProject/GameManager.cpp GameProject/GameManager.h)
add_executable(untitled ${SOURCE_FILES})