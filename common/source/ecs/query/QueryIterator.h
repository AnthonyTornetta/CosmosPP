//
// Created by cornchip on 5/18/22.
//

#pragma once

#include <cstddef>
#include <type_traits>

#include "../query/Query.h"

namespace Cosmos
{
	template<class WorldType, class EntityType>
	class QueryIterator
	{
	private:
		unsigned int m_position, m_start, m_end;
		
		WorldType *m_world;
		const Query *m_query;
		bool m_ownsQuery;
		
		QueryIterator(WorldType *world, const Query *query,
						 unsigned int position, unsigned int start, unsigned int end)
				: m_world(world), m_query(query),
				  m_ownsQuery(false),
				  m_position(position), m_start(start), m_end(end)
		{
		
		}
		
		void advance()
		{
			for (m_position++; m_position < m_end; m_position++)
			{
				if (m_query->execute(*m_world->entityAt(m_position)))
				{
					break;
				}
			}
		}
		
	public:
		QueryIterator(WorldType *world, const Query *query, bool ownsQuery = false)
				: m_world(world), m_query(query),
				  m_ownsQuery(ownsQuery),
				  m_start(-1), m_end(-1)
		{
			for (int i = 0; i < m_world->entitiesCount(); i++)
			{
				if (query->execute(*m_world->entityAt(i)))
				{
					m_start = i;
					break;
				}
			}
			
			for (int i = (int) m_world->entitiesCount() - 1; i >= 0; i--)
			{
				if (query->execute(*m_world->entityAt(i)))
				{
					m_end = i + 1; // end is out of bounds for iterators
					break;
				}
			}
			
			m_position = m_start;
		}
		
		~QueryIterator()
		{
			if (m_ownsQuery)
			{
				delete m_query;
			}
		}
		
		EntityType *operator*();
		
		EntityType *operator->();
		
		// Prefix increment
		QueryIterator<WorldType, EntityType> &operator++()
		{
			advance();
			return *this;
		}
		
		// Postfix increment
		QueryIterator<WorldType, EntityType> operator++(int)
		{
			QueryIterator tmp(m_world, m_query, m_position, m_start, m_end);
			advance();
			return tmp;
		}
		
		bool operator==(const QueryIterator<WorldType, EntityType> &b) const
		{
			return m_position == b.m_position;
		}
		
		bool operator!=(const QueryIterator<WorldType, EntityType> &b) const
		{
			return m_position != b.m_position;
		}
		
		QueryIterator<WorldType, EntityType> begin()
		{
			return {m_world, m_query, m_start, m_start, m_end};
		}
		
		QueryIterator<WorldType, EntityType> end()
		{
			return {m_world, m_query, m_end, m_start, m_end};
		}
	};
	
	class ECSWorld;
	
	typedef QueryIterator<ECSWorld, Entity> MutQueryIterator;
	typedef QueryIterator<const ECSWorld, const Entity> ConstQueryIterator;
}