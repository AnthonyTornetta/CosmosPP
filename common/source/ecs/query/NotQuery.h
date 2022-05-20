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
		~NotQuery() override;
		
		NotQuery* clone() const override;
		
	protected:
		[[nodiscard]] bool evaluate(const Entity& entity) const override;
	};
}