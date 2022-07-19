//
// Created by cornchip on 7/19/22.
//

#include "GameObject.h"
#include "Component.h"

namespace Cosmos
{
	GameObject::~GameObject() = default;
	
	Component* GameObject::getComponent(int componentID)
	{
		if(!hasComponent(componentID))
			return nullptr;
		
		return m_componentsMap.at(componentID);
	}

	void GameObject::addComponent(Ownership<Component> component)
	{
		m_componentsMap[component.value()->id()] = component.value();
		m_components.push_back(component);
	}
	
	bool GameObject::hasComponent(int compID)
	{
		return m_componentsMap.find(compID) == m_componentsMap.end();
	}
}