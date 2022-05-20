//
// Created by cornchip on 5/13/22.
//
#pragma once

#include "../ECSCallbacks.h"

#include "../query/QueryIterator.h"
#include "../query/Query.h"

namespace Cosmos
{
	template <class WorldType, class IteratorType>
	class System
	{
	public:
		typedef void (*SystemCallback)(WorldType &world, IteratorType itr);
	
	private:
		const Query *m_query;
		const SystemCallback m_callback;
	
	public:
		System(const Query *query, SystemCallback callback)
			: m_callback(callback), m_query(query)
		{
		
		}
		
		~System()
		{
			delete m_query;
		}
		
		void execute(WorldType &world, const IteratorType &itr) const
		{
			m_callback(world, itr);
		}
		
		const Query* query() const
		{
			return m_query;
		}
	};
	
	class ECSWorld;
	
	typedef System<const ECSWorld, ConstQueryIterator> ConstSystem;
	typedef System<ECSWorld, MutQueryIterator> MutSystem;
}