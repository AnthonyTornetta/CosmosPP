cmake_minimum_required(VERSION 3.21)

project(CosmosCommon VERSION 1.0.0 DESCRIPTION "cosmos common")

set(CMAKE_CXX_STANDARD 20)

add_library(CosmosCommon STATIC qu3e/scene/q3Scene.cpp qu3e/scene/q3Scene.h qu3e/math/q3Mat3.cpp qu3e/math/q3Mat3.h qu3e/math/q3Mat3.inl qu3e/math/q3Math.h qu3e/math/q3Math.inl qu3e/math/q3Quaternion.cpp qu3e/math/q3Quaternion.h qu3e/math/q3Transform.h qu3e/math/q3Transform.inl qu3e/math/q3Vec3.cpp qu3e/math/q3Vec3.h qu3e/math/q3Vec3.inl qu3e/common/q3Geometry.cpp qu3e/common/q3Geometry.h qu3e/common/q3Geometry.inl
        qu3e/common/q3Memory.cpp qu3e/common/q3Memory.h
        qu3e/common/q3Settings.h qu3e/common/q3Types.h
        qu3e/dynamics/q3Body.cpp qu3e/dynamics/q3Body.h qu3e/dynamics/q3Contact.cpp qu3e/dynamics/q3Contact.h qu3e/dynamics/q3ContactManager.cpp qu3e/dynamics/q3ContactManager.h qu3e/dynamics/q3ContactSolver.cpp qu3e/dynamics/q3ContactSolver.h qu3e/dynamics/q3Island.cpp qu3e/dynamics/q3Island.h qu3e/collision/q3Box.cpp qu3e/collision/q3Box.h qu3e/collision/q3Box.inl qu3e/collision/q3Collide.cpp qu3e/collision/q3Collide.h qu3e/debug/q3Render.h qu3e/q3.h qu3e/broadphase/q3BroadPhase.cpp qu3e/broadphase/q3BroadPhase.h qu3e/broadphase/q3DynamicAABBTree.cpp qu3e/broadphase/q3DynamicAABBTree.h qu3e/broadphase/q3DynamicAABBTree.inl source/structure/Chunk.h source/block/Block.h source/block/Blocks.h source/block/Block.cpp source/structure/Chunk.cpp source/utils/ArrayUtils.h source/utils/Tuple3.h source/structure/Structure.h source/structure/Structure.cpp source/netty/Constants.h source/ecs/query/Query.h source/ecs/query/HasQuery.h source/ecs/query/HasQuery.cpp source/ecs/component/Component.h source/ecs/entity/Entity.h source/ecs/ECSWorld.h source/ecs/entity/Entity.cpp source/structure/Dirty.h source/ecs/component/ComponentIDs.h source/ecs/component/ComponentIDs.cpp source/structure/Dirty.cpp source/ecs/Ecs.h source/ecs/query/Queries.h source/ecs/query/Query.cpp source/ecs/system/System.h source/ecs/ECSCallbacks.h source/ecs/ECSWorld.cpp CosmosCommon.h source/utils/Utils.h source/ecs/query/NotQuery.h source/ecs/query/NotQuery.cpp source/block/Blocks.cpp source/ecs/query/QueryIterator.h source/ecs/query/QueryIterator.cpp)

target_link_libraries(${PROJECT_NAME} /usr/local/lib/ libenet.a)
