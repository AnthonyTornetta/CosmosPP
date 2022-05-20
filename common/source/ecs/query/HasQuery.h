//
// Created by cornchip on 5/11/22.
//

#pragma once

#include "Query.h"

namespace Cosmos
{
	class HasQuery : public Query
	{
	private:
		int m_componentID;
		
	public:
		explicit HasQuery(int componentID, Query* next = nullptr): m_componentID(componentID), Query(next) {}
		
		HasQuery* clone() const override;
		bool evaluate(const Entity& entity) const override;
	};
}