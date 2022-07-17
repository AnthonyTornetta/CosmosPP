//
// Created by cornchip on 6/2/22.
//

#include "CosmosWorld.h"
#include "../structure/Structure.h"
#include "observers/IAddStructureObserver.h"
#include "observers/IRemoveStructureObserver.h"

#include <unordered_set>

namespace Cosmos
{
	CosmosWorld::CosmosWorld()
		: m_scene(1/60.0f)
	{
	
	};
	
	template<class T>
	void deleteObservers(std::unordered_set<void*>& deletedObservers, std::vector<Ownership<T>> vec)
	{
		for(auto &observer : vec)
		{
			if(observer.shouldDelete())
			{
				if(!deletedObservers.contains(observer.value()))
				{
					observer.deleteIfOwner();
					deletedObservers.insert(observer.value());
				}
			}
		}
	}
	
	CosmosWorld::~CosmosWorld()
	{
		for (auto &thread : m_threads)
		{
			thread->join();
		}
		
		// Prevents duplicate deletions if the same object implements 2+ interfaces
		std::unordered_set<void*> deletedObservers;
		
		deleteObservers(deletedObservers, m_addStructureObservers);
		deleteObservers(deletedObservers, m_removeStructureObservers);
		
		for (auto *structure : m_structures)
		{
			delete structure;
		}
	}
	
	void CosmosWorld::update()
	{
		
	}
	
	void CosmosWorld::addStructure(Structure *s)
	{
		for(auto &observer : m_addStructureObservers)
		{
			if(!observer.value()->onAddStructure(*this, *s))
			{
				return;
			}
		}
		
		m_structures.push_back(s);
	}
	
	void CosmosWorld::removeStructure(Structure *s)
	{
		for(auto &observer : m_removeStructureObservers)
		{
			if(!observer.value()->onRemoveStructure(*this, *s))
			{
				return;
			}
		}
		
		m_structures.erase(std::find(m_structures.begin(), m_structures.end(), s));
	}
	
	void CosmosWorld::addThread(std::unique_ptr<std::thread> thread)
	{
		m_threads.push_back(std::move(thread));
	}
	
	void CosmosWorld::addStructureAddObserver(const Ownership<IAddStructureObserver>& o)
	{
		m_addStructureObservers.push_back(o);
	}
	
	void CosmosWorld::addStructureRemoveObserver(const Ownership<IRemoveStructureObserver> &o)
	{
		m_removeStructureObservers.push_back(o);
	}
}