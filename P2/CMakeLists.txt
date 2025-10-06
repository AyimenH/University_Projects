cmake_minimum_required(VERSION 3.29)
project(P2)

set(CMAKE_CXX_STANDARD 20)

add_executable(P2 P2.cpp
        MsgStream.cpp
        MsgStream.h
        PartitionStream.cpp
        PartitionStream.h)
