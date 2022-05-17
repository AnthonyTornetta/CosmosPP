//
// Created by cornchip on 5/16/22.
//

#include "TestECS.h"

#include "CosmosCommon.h"
#include "source/structure/Dirty.h"

#include <cassert>

void assertTrue(bool condition)
{
	assert(condition);
}

int testMain()
{
	using namespace Cosmos;
	
	ECSWorld world;
	Entity* ent = world.createEntity();
	
	assertTrue(ent->addComponent(new Dirty()));
	
	world.query(NotQuery(new HasQuery(Dirty::STATIC_ID())), [](const ECSWorld& world, const Entity& entity)
	{
		assertTrue(false);
	});
	
	return 0;
}