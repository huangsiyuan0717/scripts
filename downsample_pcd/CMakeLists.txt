cmake_minimum_required(VERSION 2.8)

project(study)

set(CMAKE_BUILD_TYPE DEBUG)

find_package(PCL REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})

add_executable(downsample downsample_pcd.cpp)
target_link_libraries(downsample ${PCL_LIBRARIES})




