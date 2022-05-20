//
// Created by cornchip on 5/20/22.
//

#include "QueryIterator.h"
#include "../ECSWorld.h"
#include "../entity/Entity.h"

namespace Cosmos
{
	template<>
	Entity *QueryIterator<ECSWorld, Entity>::operator*()
	{
		return m_world->entityAtMut(m_position);
	}
	
	template<>
	const Entity *QueryIterator<const ECSWorld, const Entity>::operator*()
	{
		return m_world->entityAt(m_position);
	}
	
	template<>
	Entity *QueryIterator<ECSWorld, Entity>::operator->()
	{
		return m_world->entityAtMut(m_position);
	}
	
	template<>
	const Entity *QueryIterator<const ECSWorld, const Entity>::operator->()
	{
		return m_world->entityAt(m_position);
	}
}