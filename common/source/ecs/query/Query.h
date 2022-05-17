//
// Created by cornchip on 5/11/22.
//

#pragma once

namespace Cosmos
{
	class Entity;
	
	class Query
	{
	private:
		Query* m_next;
		
	public:
		explicit Query(Query* next = nullptr): m_next(next) {}
		~Query() = default;
		
		bool execute(const Entity& entity) const;
		
		virtual bool evaluate(const Entity& entity) const = 0;
		
		Query* next()
		{
			return m_next;
		}
	};
}