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
		virtual ~Query()
		{
			delete m_next;
		}
		
		virtual Query* clone() const = 0;
		
		bool execute(const Entity& entity) const;
		
		const Query* next() const
		{
			return m_next;
		}
	
	protected:
		virtual bool evaluate(const Entity& entity) const = 0;
	};
}