cmake_minimum_required(VERSION 3.28)
project(Csci115FinalProject)

set(CMAKE_CXX_STANDARD 14)

add_executable(Csci115FinalProject
        main.cpp
        Orders.h
        Orders.cpp
        ArrayOrderList.h
        ArrayOrderList.cpp
        SinglyOrderList.h
        SinglyOrderList.cpp
        DoublyOrderList.h)
