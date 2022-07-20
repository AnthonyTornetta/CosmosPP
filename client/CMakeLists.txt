cmake_minimum_required(VERSION 3.21)
project(CosmosClient)

set(CMAKE_CXX_STANDARD 20)

find_package(OGRE REQUIRED COMPONENTS Bites CONFIG)

add_executable(${PROJECT_NAME} main.cpp client/cube.cpp client/cube.h client/rendering/RenderedStructure.cpp client/rendering/RenderedStructure.h client/rendering/Renderable.h tests/TestECS.cpp tests/TestECS.h client/rendering/DirtyNeedsRendered.h client/rendering/DirtyNeedsRendered.cpp client/rendering/DoingRendering.h client/rendering/DoingRendering.cpp client/rendering/NeedsOpenGLUpdated.h client/rendering/NeedsOpenGLUpdated.cpp client/world/ClientWorld.h client/world/ClientWorld.cpp client/rendering/StructureRenderData.h client/rendering/StructureRenderData.cpp client/rendering/ChunkRenderData.h client/rendering/ChunkRenderData.cpp client/netty/ClientPacketLoader.h client/netty/ClientPacketLoader.cpp)

# This clever hackery from https://stackoverflow.com/questions/7980784/cmake-add-sub-directory-which-is-not-sub-directory-on-real-directory
# I'm bad at cmake so this is how I could get this to work. There's probably a better way
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../common ${CMAKE_CURRENT_BINARY_DIR}/common)

target_include_directories(${PROJECT_NAME} PUBLIC ../common)

target_link_directories(${PROJECT_NAME} PUBLIC ../common /usr/local/lib/OGRE/)

target_link_libraries(${PROJECT_NAME} OgreBites CosmosCommon)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
