//
// Created by cornchip on 5/11/22.
//

#pragma once

namespace Cosmos
{
	class Component
	{
	private:
		bool m_entityShouldDelete;
		
	public:
		Component(): m_entityShouldDelete(false) {}
		virtual ~Component() = default;
		
		[[nodiscard]] virtual int id() const = 0;
		
		[[nodiscard]] virtual bool canHaveDuplicates() const
		{
			return false;
		}
		
		/**
		 * Used & set in entity class
		 * If this is true, the Component will be deleted when the entity is deleted
		 * @return If this is true, the Component will be deleted when the entity is deleted
		 */
		[[nodiscard]] bool entityShouldDelete() const
		{
			return m_entityShouldDelete;
		}
		
		/**
		 * Used & set in entity class
		 * If this is true, the Component will be deleted when the entity is deleted
		 * @param b If this is true, the Component will be deleted when the entity is deleted
		 */
		void entityShouldDelete(bool b)
		{
			m_entityShouldDelete = b;
		}
	};
}