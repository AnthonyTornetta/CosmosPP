//
// Created by cornchip on 4/28/22.
//

#include "Block.h"

#include <utility>

namespace Cosmos
{
	Block::Block(std::string block_name)
		: m_id(0), m_block_name(std::move(block_name))
	{
	
	}
	
	bool Block::operator==(const Block &b) const
	{
		return m_id == b.m_id;
	}
	
	bool Block::operator!=(const Block &b) const
	{
		return m_id != b.m_id;
	}
	
	bool Block::hasCollision() const
	{
		return true;
	}
}