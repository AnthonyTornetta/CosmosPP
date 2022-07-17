//
// Created by cornchip on 7/16/22.
//
#include "StructureBlock.h"

#include "Structure.h"

namespace Cosmos
{
	StructureBlock::StructureBlock(int x, int y, int z, Structure &s)
			:m_x(x), m_y(y), m_z(z), m_structure(s)
	{
	
	}
	
	const Block &StructureBlock::block() const
	{
		return m_structure.block(x(), y(), z());
	}
	
	void StructureBlock::block(const Block &block)
	{
		m_structure.block(x(), y(), z(), block);
	}
}