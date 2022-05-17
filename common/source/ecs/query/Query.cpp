//
// Created by cornchip on 5/13/22.
//

#include "Query.h"

namespace Cosmos
{
	bool Query::execute(const Entity &entity) const
	{
		if(!evaluate(entity))
			return false;
		
		if(!m_next)
			return true;
		
		return m_next->execute(entity); // tail recursion - no stack impact
	}
}