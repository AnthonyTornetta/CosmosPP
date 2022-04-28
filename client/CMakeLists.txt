cmake_minimum_required(VERSION 3.21)
project(CosmosClient)

set(CMAKE_CXX_STANDARD 14)

link_directories(/usr/local/lib/OGRE/)

include_directories(../common)

find_package(OGRE REQUIRED COMPONENTS Bites CONFIG)

add_executable(${PROJECT_NAME} main.cpp source/cube.cpp include/cube.h)

target_include_directories(${PROJECT_NAME} PUBLIC ../common)

target_link_directories(${PROJECT_NAME} PUBLIC ../common)

target_link_libraries(${PROJECT_NAME} OgreBites CosmosCommon)