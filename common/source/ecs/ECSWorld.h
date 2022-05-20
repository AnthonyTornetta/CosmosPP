//
// Created by cornchip on 5/11/22.
//

#pragma once

#include <vector>

#include "system/System.h"

#include "entity/Entity.h"
#include "query/Query.h"
#include "ECSCallbacks.h"

#include "query/QueryIterator.h"

namespace Cosmos
{
	class ECSWorld
	{
	private:
		std::vector<Entity*> m_entities;
		
		std::vector<const ConstSystem*> m_systems;
		std::vector<const MutSystem*> m_mutSystems;
	
	public:
		ECSWorld();
		~ECSWorld();
		
		Entity* createEntity();
		void destroyEntity(Entity* entity);
		
		void runSystems();
		
		void addSystem(const ConstSystem* s);
		void addMutSystem(const MutSystem* s);
		
		void query(const Query& query, ECSCallbacks::Callback callback) const;
		void queryMut(const Query& query, ECSCallbacks::CallbackMut callback);
		
		int entitiesCount() const;
		
		const Entity *entityAt(unsigned int i) const;
		Entity *entityAtMut(unsigned int i);
	};
}