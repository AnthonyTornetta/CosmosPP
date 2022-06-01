//
// Created by cornchip on 5/13/22.
//

#include "ECSWorld.h"

#include <cassert>

#include <thread>

namespace Cosmos
{
	ECSWorld::ECSWorld() = default;
	ECSWorld::~ECSWorld()
	{
		for(const ConstSystem* sys: m_systems)
		{
			assert(sys != nullptr);
			delete sys;
		}
		
		for(const MutSystem* sys: m_mutSystems)
		{
			assert(sys != nullptr);
			delete sys;
		}
		
		for(const Entity* ent: m_entities)
		{
			assert(ent != nullptr);
			delete ent;
		}
	}
	
	Entity* ECSWorld::createEntity()
	{
		m_entities.push_back(new Entity());
		return m_entities[m_entities.size() - 1];
	}
	
	void ECSWorld::destroyEntity(Entity *entity)
	{
		assert(entity != nullptr);
		
		for(int i = 0; i < m_entities.size(); i++)
		{
			if(m_entities[i] == entity)
			{
				delete m_entities[i];
				m_entities.erase(i + m_entities.begin());
				break;
			}
		}
	}
	
	void ECSWorld::query(const Query &query, ECSCallbacks::Callback const callback) const
	{
		for(const Entity* ent : m_entities)
		{
			if(query.execute(*ent))
			{
				callback(*this, *ent);
			}
		}
	}
	
	void ECSWorld::queryMut(const Query &query, ECSCallbacks::CallbackMut const callback)
	{
		for(Entity* ent : m_entities)
		{
			if(query.execute(*ent))
			{
				callback(*this, *ent);
			}
		}
	}
	
	void ECSWorld::addMutSystem(const MutSystem* s)
	{
		assert(s != nullptr);
		
		m_mutSystems.push_back(s);
	}
	
	void ECSWorld::addSystem(const ConstSystem* s)
	{
		assert(s != nullptr);
		
		m_systems.push_back(s);
	}
	
	void ECSWorld::runSystems()
	{
		auto* threads = new std::thread[m_systems.size()];
		
		for (int i = 0; i < m_systems.size(); i++)//const System* sys : m_systems)
		{
			auto *sys = m_systems[i];
			assert(sys != nullptr);
			
			threads[i] = std::thread([this, sys]()
			{
				sys->execute(*this, ConstQueryIterator(this, sys->query()));
			});
		}
		
		for(int i = 0; i < m_systems.size(); i++)
			threads[i].join();
		
		delete[] threads;
		
		for (const MutSystem* sys : m_mutSystems)
		{
			assert(sys != nullptr);
			
			sys->execute(*this, MutQueryIterator(this, sys->query()));
		}
	}
	
	int ECSWorld::entitiesCount() const
	{
		return (int)m_entities.size();
	}
	
	const Entity *ECSWorld::entityAt(unsigned int i) const
	{
		assert(i < m_entities.size());
		
		return m_entities[i];
	}
	
	Entity *ECSWorld::entityAtMut(unsigned int i)
	{
		assert(i < m_entities.size());
		
		return m_entities[i];
	}
}