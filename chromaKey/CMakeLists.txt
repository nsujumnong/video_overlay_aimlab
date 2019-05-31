cmake_minimum_required(VERSION 3.12)
project(chromaKey)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
set(CMAKE_CXX_STANDARD 11)

add_executable(chromaKey main.cpp)
target_link_libraries(chromaKey ${OpenCV_LIBS})