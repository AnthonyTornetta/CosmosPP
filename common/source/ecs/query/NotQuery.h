//
// Created by cornchip on 5/16/22.
//

#pragma once

#include "Query.h"

namespace Cosmos
{
	class NotQuery : public Query
	{
	private:
		Query* m_actual;
		
	public:
		explicit NotQuery(Query *actual, Query* next = nullptr);
		~NotQuery();
		
		[[nodiscard]] virtual bool evaluate(const Entity& entity) const;
	};
}