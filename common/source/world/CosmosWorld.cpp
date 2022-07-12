//
// Created by cornchip on 6/2/22.
//

#include "CosmosWorld.h"
#include "../structure/Structure.h"

namespace Cosmos
{
	CosmosWorld::CosmosWorld() = default;
	
	CosmosWorld::~CosmosWorld()
	{
		for (auto &thread : m_threads)
		{
			thread->join();
		}
		
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
		m_structures.push_back(s);
	}
	
	void CosmosWorld::addThread(std::unique_ptr<std::thread> thread)
	{
		m_threads.push_back(std::move(thread));
	}
}