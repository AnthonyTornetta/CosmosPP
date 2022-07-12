//
// Created by cornchip on 6/2/22.
//

#pragma once

#include <vector>
#include <thread>


namespace Cosmos
{
	class Structure;
	
	class CosmosWorld
	{
	private:
		std::vector<Structure*> m_structures;
		
		std::vector<std::unique_ptr<std::thread>> m_threads;
	
	public:
		CosmosWorld();
		~CosmosWorld();
		
		virtual void addThread(std::unique_ptr<std::thread> thread);
		
		virtual void addStructure(Structure* s);
		
		virtual void update();
	};
}