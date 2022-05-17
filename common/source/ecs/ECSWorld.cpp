//
// Created by cornchip on 5/13/22.
//

#include "ECSWorld.h"

namespace Cosmos
{
	Entity* ECSWorld::createEntity()
	{
		entities.emplace_back();
		return &entities[entities.size() - 1];
	}
	
	void ECSWorld::destroyEntity(Entity *entity)
	{
		for(int i = 0; i < entities.size(); i++)
		{
			if(&entities[i] == entity)
			{
				entities.erase(i + entities.begin());
			}
		}
	}
	
	void ECSWorld::query(const Query &query, ECSCallbacks::Callback const callback) const
	{
		for(const Entity& ent : entities)
		{
			if(query.execute(ent))
			{
				callback(*this, ent);
			}
		}
	}
	
	void ECSWorld::queryMut(const Query &query, ECSCallbacks::CallbackMut const callback)
	{
		for(Entity& ent : entities)
		{
			if(query.execute(ent))
			{
				callback(*this, ent);
			}
		}
	}
	
	ECSWorld::~ECSWorld()
	{
	
	}
}