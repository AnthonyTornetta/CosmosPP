cmake_minimum_required(VERSION 3.21)
project(CosmosPP)

set(CMAKE_CXX_STANDARD 14)

link_directories(/usr/local/lib/OGRE/)

find_package(OGRE REQUIRED COMPONENTS Bites CONFIG)

add_executable(CosmosPP main.cpp qu3e/scene/q3Scene.cpp qu3e/scene/q3Scene.h qu3e/math/q3Mat3.cpp qu3e/math/q3Mat3.h qu3e/math/q3Mat3.inl qu3e/math/q3Math.h qu3e/math/q3Math.inl qu3e/math/q3Quaternion.cpp qu3e/math/q3Quaternion.h qu3e/math/q3Transform.h qu3e/math/q3Transform.inl qu3e/math/q3Vec3.cpp qu3e/math/q3Vec3.h qu3e/math/q3Vec3.inl qu3e/common/q3Geometry.cpp qu3e/common/q3Geometry.h qu3e/common/q3Geometry.inl qu3e/common/q3Memory.cpp qu3e/common/q3Memory.h qu3e/common/q3Settings.h qu3e/common/q3Types.h qu3e/dynamics/q3Body.cpp qu3e/dynamics/q3Body.h qu3e/dynamics/q3Contact.cpp qu3e/dynamics/q3Contact.h qu3e/dynamics/q3ContactManager.cpp qu3e/dynamics/q3ContactManager.h qu3e/dynamics/q3ContactSolver.cpp qu3e/dynamics/q3ContactSolver.h qu3e/dynamics/q3Island.cpp qu3e/dynamics/q3Island.h qu3e/collision/q3Box.cpp qu3e/collision/q3Box.h qu3e/collision/q3Box.inl qu3e/collision/q3Collide.cpp qu3e/collision/q3Collide.h qu3e/debug/q3Render.h qu3e/q3.h qu3e/broadphase/q3BroadPhase.cpp qu3e/broadphase/q3BroadPhase.h qu3e/broadphase/q3DynamicAABBTree.cpp qu3e/broadphase/q3DynamicAABBTree.h qu3e/broadphase/q3DynamicAABBTree.inl include/cube.h source/cube.cpp)

target_link_libraries(CosmosPP OgreBites)