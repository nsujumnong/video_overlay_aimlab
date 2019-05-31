cmake_minimum_required(VERSION 3.12)
project(vid_overlay)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
set(CMAKE_CXX_STANDARD 11)

add_executable(vid_overlay main.cpp)
target_link_libraries(vid_overlay ${OpenCV_LIBS})