cmake_minimum_required(VERSION 3.21)
project(statemachinetool)

set(CMAKE_CXX_STANDARD 14)

add_executable(statemachinetool main.cpp StateMachineManager.cpp StateMachineManager.h)
