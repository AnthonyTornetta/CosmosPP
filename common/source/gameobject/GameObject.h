//
// Created by cornchip on 7/17/22.
//

#pragma once

#include <vector>
#include <map>
#include "../utils/Ownership.h"

namespace Cosmos
{
	class Component;
	
	class GameObject
	{
	private:
		std::vector<Ownership<Component>> m_components;
		std::map<int, Component*> m_componentsMap;
		
	public:
		GameObject() = default;
		~GameObject();
		
		[[nodiscard]] bool hasComponent(int compID);
		
		[[nodiscard]] Component* getComponent(int componentID);
		
		void addComponent(Ownership<Component> component);
	};
}
