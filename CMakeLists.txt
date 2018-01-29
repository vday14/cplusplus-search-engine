cmake_minimum_required(VERSION 3.9)
project(eecs398_search)

set(CMAKE_CXX_STANDARD 11)

add_executable(eecs398_search
        main.cpp
        ProducerConsumerQueue.cpp
        ProducerConsumerQueue.h
        ProducerConsumerQueue_test.cpp Parser.cpp)
