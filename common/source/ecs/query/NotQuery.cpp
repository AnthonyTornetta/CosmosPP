//
// Created by cornchip on 5/16/22.
//

#include "NotQuery.h"

namespace Cosmos
{
	NotQuery::NotQuery(Query *actual, Query *next)
		: m_actual(actual), Query(next)
	{
	
	}
	
	NotQuery::~NotQuery()
	{
		delete m_actual;
	}
	
	bool NotQuery::evaluate(const Entity &entity) const
	{
		return !m_actual->execute(entity);
	}
	
	NotQuery *NotQuery::clone() const
	{
		return new NotQuery(m_actual->clone(), next()->clone());
	}
}