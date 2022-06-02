//
// Created by cornchip on 4/28/22.
//
#include "Chunk.h"

#include "../block/Blocks.h"

#include "../utils/ArrayUtils.h"

#include <cassert>

#include "../ecs/component/ComponentIDs.h"

namespace Cosmos
{
	Chunk::Chunk()
			: m_blocks(new unsigned short[WIDTH * HEIGHT * LENGTH])
	{
	
	}
	
	Chunk::~Chunk()
	{
		delete[] m_blocks;
	}
	
	void Chunk::blockAt(int x, int y, int z, const Block &b)
	{
		assert(withinChunkCoords(x, y, z));
		
		m_blocks[flatten(x, y, z, WIDTH, HEIGHT)] = b.id();
	}
	
	const Block &Chunk::blockAt(int x, int y, int z) const
	{
		assert(withinChunkCoords(x, y, z));
		
		return Blocks::getBlock(m_blocks[flatten(x, y, z, WIDTH, HEIGHT)]);
	}
	
	bool Chunk::withinChunkCoords(int x, int y, int z) const
	{
		return x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT && z >= 0 && z < LENGTH;
	}
	
	int Chunk::id() const
	{
		return STATIC_ID();
	}
	
	int Chunk::STATIC_ID()
	{
		static int id = ComponentIDs::createID();
		
		return id;
	}
	
	bool Chunk::canHaveDuplicates() const
	{
		return true;
	}
}

