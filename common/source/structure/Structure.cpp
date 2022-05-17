//
// Created by cornchip on 4/29/22.
//
#include "Structure.h"

#include <cassert>

#include "../utils/ArrayUtils.h"

#include "../ecs/component/ComponentIDs.h"
#include "../ecs/entity/Entity.h"

namespace Cosmos
{
	Structure::Structure(int chunksX, int chunksY, int chunksZ, Entity* entity) :
			m_chunksX(chunksX), m_chunksY(chunksY), m_chunksZ(chunksZ),
			m_dirty(false), m_chunks(new Chunk[chunksX * chunksY * chunksZ]),
			m_entity(entity)
	{
		for(int i = 0; i < chunksX * chunksY * chunksZ; i++)
		{
			bool res = m_entity->addComponent(&m_chunks[i], false, false);
			assert(res);
		}
	}
	
	Structure::~Structure()
	{
		m_entity->removeAllComponentsWithID(Chunk::STATIC_ID());
		
		delete[] m_chunks;
	}
	
	const Block &Structure::block(int x, int y, int z) const
	{
		assert(withinBlocks(x, y, z));
		
		int chunkIndex = flatten(x, y, z, m_chunksX, m_chunksY);
		
		return m_chunks[chunkIndex].blockAt(x / 16, y / 16, z / 16);
	}
	
	void Structure::block(int x, int y, int z, const Block &b)
	{
		assert(withinBlocks(x, y, z));
		
		int chunkIndex = flatten(x, y, z, m_chunksX, m_chunksY);
		
		m_chunks[chunkIndex].blockAt(x / 16, y / 16, z / 16, b);
	}
	
	bool Structure::withinBlocks(int x, int y, int z) const
	{
		return x >= 0 && x < blocksWidth() && y >= 0 && y < blocksHeight() && z >= 0 && z < blocksLength();
	}
	
	int Structure::id()
	{
		return STATIC_ID();
	}
	
	int Structure::STATIC_ID()
	{
		static int id = ComponentIDs::createID();
		
		return id;
	}
}

