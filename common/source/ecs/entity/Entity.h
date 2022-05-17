//
// Created by cornchip on 5/11/22.
//

#pragma once

#include <map>
#include <vector>
#include <climits>

#include "../component/Component.h"

namespace Cosmos
{
	class Entity
	{
	private:
		std::map<int, std::vector<Component*>> m_componentsMap;
		std::vector<Component*> m_componentsVec;
		
	public:
		Entity() = default;
		~Entity();
		
		/**
		 * Adds a component to this entity.  This component should be unique to this entity.  The component
		 * is deleted when this entity is deleted if hasOwnership is true (Defaults to true).
		 * If hasOwnership is true, do not manually delete this component
		 * @param comp The component to add - deleted when this entity is deleted
		 * @param deleteIfFull Deletes the component if the component cannot be added
		 * @param hasOwnership If this is true, the component will be deleted when this is deleted.
		 * @return True if it was added, false if not
		 */
		bool addComponent(Component* comp, bool hasOwnership = true, bool deleteIfFull = true);
		
		/**
		 * Removes the component and deletes it.
		 * Fails assertion if the component doesn't exist. Use hasComponent to check
		 * @param compID The component ID to remove
		 */
		void removeAllComponentsWithID(int compID);
		[[nodiscard]] bool hasComponent(int compID) const;
		
		/**
		 * Gets the first component registered with that ID.  Useful for components that only support one per entity
		 * @param compID The component's ID
		 * @return The first component found, or nullptr if not found
		 */
		[[nodiscard]] const Component* getFirstComponent(int compID) const;
		
		/**
		 * Gets all the components registered with that ID.
		 * @param compID The component's ID
		 * @return The first component found, or empty vector if none present
		 */
		[[nodiscard]] const std::vector<Component*>& getComponents(int compID) const;
		
		/**
		 * Gets the first component registered with that ID.  Useful for components that only support one per entity
		 * @param compID The component's ID
		 * @return The first component found, or nullptr if not found
		 */
		[[nodiscard]] Component* getFirstComponentMut(int compID);
		
		/**
		 * Gets all the components registered with that ID.
		 * @param compID The component's ID
		 * @return The first component found, or empty vector if none present
		 */
		[[nodiscard]] std::vector<Component*>& getComponentsMut(int compID);
	};
}