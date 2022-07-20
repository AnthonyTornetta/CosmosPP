cmake_minimum_required(VERSION 3.21)
project(CosmosServer)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} main.cpp server/netty/ServerPacketLoader.h server/netty/ServerPacketLoader.cpp)

# This clever hackery from https://stackoverflow.com/questions/7980784/cmake-add-sub-directory-which-is-not-sub-directory-on-real-directory
# I'm bad at cmake so this is how I could get this to work. There's probably a better way
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../common ${CMAKE_CURRENT_BINARY_DIR}/common)

target_include_directories(${PROJECT_NAME} PUBLIC ../common)

target_link_directories(${PROJECT_NAME} PUBLIC ../common)

target_link_libraries(${PROJECT_NAME} OgreBites CosmosCommon)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
