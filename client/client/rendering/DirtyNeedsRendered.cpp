//
// Created by cornchip on 6/1/22.
//
#include <source/ecs/component/ComponentIDs.h>
#include "DirtyNeedsRendered.h"

namespace Cosmos::Rendering
{
	DirtyNeedsRendered::DirtyNeedsRendered(int chunkX, int chunkY, int chunkZ)
		: m_chunkX(chunkX), m_chunkY(chunkY), m_chunkZ(chunkZ)
	{
	
	}
	
	int DirtyNeedsRendered::STATIC_ID()
	{
		static int id = ComponentIDs::createID();
		
		return id;
	}
	
	int DirtyNeedsRendered::id() const
	{
		return STATIC_ID();
	}
	
	int DirtyNeedsRendered::chunkX() const
	{
		return m_chunkX;
	}
	
	int DirtyNeedsRendered::chunkY() const
	{
		return m_chunkY;
	}
	
	int DirtyNeedsRendered::chunkZ() const
	{
		return m_chunkZ;
	}
	
	bool DirtyNeedsRendered::canHaveDuplicates() const
	{
		return true;
	}
}