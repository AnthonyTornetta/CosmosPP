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
	static int nextID()
	{
		static int SID = 1;
		
		return SID++;
	}
	
	Structure::Structure(int chunksX, int chunksY, int chunksZ) :
			m_chunksX(chunksX), m_chunksY(chunksY), m_chunksZ(chunksZ),
			m_dirty(false), m_chunks(new Chunk[chunksX * chunksY * chunksZ]),
			m_id(nextID())
	{
	
	}
	
	Structure::~Structure()
	{
		delete[] m_chunks;
	}
	
	const Block &Structure::block(int x, int y, int z) const
	{
		assert(withinBlocks(x, y, z));
		
		int chunkIndex = flatten(x / Chunk::WIDTH, y / Chunk::HEIGHT, z / Chunk::LENGTH, m_chunksX, m_chunksY);
		
		return m_chunks[chunkIndex].blockAt(x % Chunk::WIDTH, y % Chunk::HEIGHT, z % Chunk::LENGTH);
	}
	
	void Structure::block(int x, int y, int z, const Block &b)
	{
		assert(withinBlocks(x, y, z));
		
		int chunkIndex = flatten(x / Chunk::WIDTH, y / Chunk::HEIGHT, z / Chunk::LENGTH, m_chunksX, m_chunksY);
		
		int xx = x % Chunk::WIDTH;
		int yy = y % Chunk::HEIGHT;
		int zz = z % Chunk::LENGTH;
		
		const Block& old = m_chunks[chunkIndex].blockAt(xx, yy, zz);
		
		m_chunks[chunkIndex].blockAt(xx, yy, zz, b);
		
		for(auto *callback : m_BlockCallbacks)
		{
			callback->onBlockUpdate(*this, old, x, y, z);
		}
	}
	
	bool Structure::withinBlocks(int x, int y, int z) const
	{
		return x >= 0 && x < blocksWidth() && y >= 0 && y < blocksHeight() && z >= 0 && z < blocksLength();
	}
	
	int Structure::id() const
	{
		return m_id;
	}
	
	int Structure::STATIC_ID()
	{
		static int id = ComponentIDs::createID();
		
		return id;
	}
	
	void Structure::addBlockChangeListener(IHasBlockChangeCallback* callback)
	{
		m_BlockCallbacks.push_back(callback);
	}
	
	const Chunk &Structure::chunkAt(int cx, int cy, int cz)
	{
		assert(cx >= 0 && cx < chunksWidth());
		assert(cy >= 0 && cx < chunksHeight());
		assert(cz >= 0 && cx < chunksLength());
		
		return m_chunks[flatten(cx, cy, cz, chunksWidth(), chunksHeight())];
	}
}

