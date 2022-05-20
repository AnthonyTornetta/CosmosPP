//
// Created by cornchip on 5/11/22.
//
#include "HasQuery.h"

#include "../entity/Entity.h"

namespace Cosmos
{
	bool HasQuery::evaluate(const Entity& entity) const
	{
		return entity.hasComponent(m_componentID);
	}
	
	HasQuery *HasQuery::clone() const
	{
		return new HasQuery(m_componentID, next()->clone());
	}
}