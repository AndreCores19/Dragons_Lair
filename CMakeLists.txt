cmake_minimum_required(VERSION 4.1)
project(Dragons_Lair)

set(CMAKE_CXX_STANDARD 20)

add_executable(Dragons_Lair main.cpp
        World.cpp
        World.h
        Region.cpp
        Region.h
        List.cpp
        List.h
)
