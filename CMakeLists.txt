cmake_minimum_required(VERSION 3.28)
project(Csci115FinalProject)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_OSX_SYSROOT "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX15.2.sdk")
find_package(Python3 REQUIRED)
message(STATUS "Python3 executable: ${Python3_EXECUTABLE}")


add_executable(Csci115FinalProject
        main.cpp
        Orders.h
        Orders.cpp
        ArrayOrderList.h
        ArrayOrderList.cpp
        SinglyOrderList.h
        SinglyOrderList.cpp
        DoublyOrderList.h
        DoublyOrderList.cpp
        SkipOrderList.h
        SkipOrderList.cpp
        OrderSorting.cpp
        OrderSorting.h
        BstOrderList.h
        BstOrderList.cpp
        AvlOrderList.h
        AvlOrderList.cpp
        RouteOptimization.h
        RouteOptimization.cpp
        TimedOperations.h
        TimedOperations.cpp)
