//
// Created by cornchip on 6/2/22.
//

#pragma once

#include <vector>
#include <thread>
#include "../../qu3e/q3.h"
#include "../utils/Ownership.h"

namespace Cosmos
{
	class Structure;
	class IAddStructureObserver;
	class IRemoveStructureObserver;
	
	class CosmosWorld
	{
	private:
		std::vector<Structure*> m_structures;
		
		std::vector<std::unique_ptr<std::thread>> m_threads;
		
		std::vector<Ownership<IAddStructureObserver>> m_addStructureObservers;
		std::vector<Ownership<IRemoveStructureObserver>> m_removeStructureObservers;
		
		q3::q3Scene m_scene;
	
	public:
		CosmosWorld();
		~CosmosWorld();
		
		virtual void addThread(std::unique_ptr<std::thread> thread);
		
		virtual void addStructure(Structure* s);
		virtual void removeStructure(Structure* s);
		
		/**
		 * Adds an observer that is called whenever the structure.
		 * @param o The observer
		 */
		void addStructureAddObserver(const Ownership<IAddStructureObserver>& o);
		
		void addStructureRemoveObserver(const Ownership<IRemoveStructureObserver>& o);
		
		virtual void update();
	};
}