//
// Created by cornchip on 5/11/22.
//

#include "Entity.h"

#include <cassert>

namespace Cosmos
{
	Entity::~Entity()
	{
		while(!m_componentsVec.empty())
		{
			Component* comp = m_componentsVec[m_componentsVec.size() - 1];
			
			assert(comp != nullptr);
			
			std::vector<Component*>& comps = m_componentsMap[comp->id()];
			
			// Should be in the same order as vector list
			// If this ever becomes untrue, you will have to search through the m_componentsMap[comp->id()] for this component then remove it.
			// Do this because some components may search that map for components to delete and can crash if there is a deleted object in that map still
			// (this is why it is also removed from the componentsVec)
			assert(comp == comps[comps.size() - 1]);
			
			m_componentsMap[comp->id()].pop_back();
			
			m_componentsVec.pop_back();
			
			if(comp->entityShouldDelete())
				delete comp;
		}
	}
	
	bool Entity::addComponent(Component* comp, bool hasOwnership, bool deleteIfFull)
	{
		assert(comp != nullptr);
		
		if (!comp->canHaveDuplicates() && hasComponent(comp->id()))
		{
			if(deleteIfFull)
				delete comp;
			
			return false;
		}
		
		comp->entityShouldDelete(hasOwnership);
		
		m_componentsMap[comp->id()].push_back(comp);
		
		m_componentsVec.push_back(comp);
		
		return true;
	}
	
	void Entity::removeAllComponentsWithID(int compID)
	{
		assert(hasComponent(compID));
		
		int nToErase = (int) m_componentsMap.at(compID).size();
		m_componentsMap.erase(compID);

		#ifndef NDEBUG
		
		// check if the amount to erase actually matches up
		int count = 0;
		for(auto & c : m_componentsVec)
		{
			assert(c != nullptr);
			
			count += (c->id() == compID);
		}
		assert(count == nToErase);
		
		#endif
		
		for(int i = 0; nToErase; i++)
		{
			assert(i < m_componentsVec.size());
			
			if(m_componentsVec[i]->id() == compID)
			{
				Component* comp = m_componentsVec[i];
				
				assert(comp != nullptr);
				
				m_componentsVec.erase(m_componentsVec.begin() + i);
				i--;
				
				if(comp->entityShouldDelete())
					delete comp;
				
				nToErase--;
			}
		}
		
		assert(nToErase == 0);
	}
	
	bool Entity::hasComponent(int compID) const
	{
		return m_componentsMap.contains(compID);
	}
	
	const std::vector<Component*>& Entity::getComponents(int compID) const
	{
		return m_componentsMap.at(compID);
	}
	
	const Component* Entity::getFirstComponent(int compID) const
	{
		if(!hasComponent(compID))
			return nullptr;
		
		return getComponents(compID)[0];
	}
	
	Component *Entity::getFirstComponentMut(int compID)
	{
		if(!hasComponent(compID))
			return nullptr;
		
		return getComponents(compID)[0];
	}
	
	std::vector<Component *> &Entity::getComponentsMut(int compID)
	{
		assert(hasComponent(compID));
		
		return m_componentsMap.at(compID);
	}
}