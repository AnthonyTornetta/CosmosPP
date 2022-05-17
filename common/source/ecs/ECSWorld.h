//
// Created by cornchip on 5/11/22.
//

#pragma once

#include <vector>

#include "entity/Entity.h"
#include "query/Query.h"
#include "ECSCallbacks.h"

namespace Cosmos
{
	class ECSWorld
	{
	private:
		std::vector<Entity> entities;
	public:
		~ECSWorld();
		
		Entity* createEntity();
		void destroyEntity(Entity* entity);
		
		auto entitiesBegin()
		{
			return entities.begin();
		}
		
		auto entitiesEnd()
		{
			return entities.end();
		}
		
		void query(const Query& query, ECSCallbacks::Callback callback) const;
		void queryMut(const Query& query, ECSCallbacks::CallbackMut callback);
	};
}