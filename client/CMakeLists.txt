cmake_minimum_required(VERSION 3.21)
project(CosmosClient)

set(CMAKE_CXX_STANDARD 14)

find_package(OGRE REQUIRED COMPONENTS Bites CONFIG)

add_executable(${PROJECT_NAME} main.cpp source/cube.cpp source/cube.h source/rendering/RenderedStructure.cpp source/rendering/RenderedStructure.h source/rendering/Renderable.h tests/TestECS.cpp tests/TestECS.h)

# This clever hackery from https://stackoverflow.com/questions/7980784/cmake-add-sub-directory-which-is-not-sub-directory-on-real-directory
# I'm bad at cmake so this is how I could get this to work. There's probably a better way
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../common ${CMAKE_CURRENT_BINARY_DIR}/common)

target_include_directories(${PROJECT_NAME} PUBLIC ../common)

target_link_directories(${PROJECT_NAME} PUBLIC ../common /usr/local/lib/OGRE/)

target_link_libraries(${PROJECT_NAME} OgreBites CosmosCommon)
