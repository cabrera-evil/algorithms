cmake_minimum_required(VERSION 3.24)
project(algorithms)

set(CMAKE_CXX_STANDARD 14)

add_executable(insertion sorting/insertionSort.cpp)
add_executable(selection sorting/selectionSort.cpp)
add_executable(bubble sorting/bubbleSort.cpp)
