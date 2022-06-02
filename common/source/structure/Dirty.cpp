//
// Created by cornchip on 5/12/22.
//
#include "Dirty.h"
#include "../ecs/component/ComponentIDs.h"

namespace Cosmos
{
	int Dirty::id() const
	{
		return STATIC_ID();
	}
	
	Dirty::~Dirty() = default;
	
	int Dirty::STATIC_ID()
	{
		static int id = ComponentIDs::createID();
		
		return id;
	}
}