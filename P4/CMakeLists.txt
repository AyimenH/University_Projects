cmake_minimum_required(VERSION 3.29)
project(P4)

set(CMAKE_CXX_STANDARD 20)

add_executable(P4 P4.cpp
        MsgStream.cpp
        MsgStream.h
        PartitionStream.cpp
        PartitionStream.h
        DurableStream.cpp
        DurableStream.h)
