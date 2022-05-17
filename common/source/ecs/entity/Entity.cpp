//
// Created by cornchip on 5/11/22.
//

#include "Entity.h"

#include <cassert>

namespace Cosmos
{
	Entity::~Entity()
	{
		for (auto c: m_componentsVec)
			if(c->entityShouldDelete())
				delete c;
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
		
		int nErased = m_componentsMap.erase(compID);
		for(int i = 0; nErased; i++)
		{
			if(m_componentsVec[i]->id() == compID)
			{
				Component* comp = m_componentsVec[i];
				
				m_componentsVec.erase(m_componentsVec.begin() + i);
				
				if(comp->entityShouldDelete())
					delete comp;
				
				nErased--;
				
				if(!nErased)
					return;
			}
		}
		
		// Should never reach this point
		assert(false);
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