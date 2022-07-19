//
// Created by cornchip on 4/28/22.
//

#pragma once

#include <vector>
#include "Chunk.h"

#include "IHasBlockChangeCallback.h"

#include <map>
#include "../utils/Ownership.h"

namespace Cosmos
{
	class Entity;
	
	/**
	 * Represents a collection of chunks
	 */
	class Structure
	{
	
	
	private:
		Chunk* m_chunks;
		
		int m_chunksX, m_chunksY, m_chunksZ;
		
		bool m_dirty;
		
		std::vector<Ownership<IHasBlockChangeCallback>> m_blockCallbacks;
		
		const int m_id;
		
	public:
		/**
		 * Represents a collection of chunks
		 * @param chunksX The number of chunks in the X direction
		 * @param chunksY The number of chunks in the Y direction
		 * @param chunksZ The number of chunks in the Z direction
		 */
		Structure(int chunksX, int chunksY, int chunksZ);
		~Structure();
		
		[[nodiscard]] bool withinBlocks(int x, int y, int z) const;
		
		/**
		 * Gets the type of block where 0,0,0 is the left bottom back and right top front
		 * @param x [0, blocksWidth())
		 * @param y [0, blocksHeight())
		 * @param z [0, blocksLength())
		 * @return type of block at that location
		 */
		[[nodiscard]] const Block& block(int x, int y, int z) const;
		
		/**
		 * Sets the type of block where 0,0,0 is the left bottom back and right top front
		 * @param x [0, blocksWidth())
		 * @param y [0, blocksHeight())
		 * @param z [0, blocksLength())
		 * @param b The type to set it to
		 */
		void block(int x, int y, int z, const Block& b);
		
		/**
		 * If the structure's blocks have been modified, this will be true
		 * @return If the structure's blocks have been modified, this will be true
		 */
		[[nodiscard]] inline bool dirty() const
		{
			return m_dirty;
		}
		
		[[nodiscard]] inline int blocksWidth() const
		{
			return m_chunksX * Chunk::WIDTH;
		}
		
		[[nodiscard]] inline int blocksHeight() const
		{
			return m_chunksY * Chunk::HEIGHT;
		}
		
		[[nodiscard]] inline int blocksLength() const
		{
			return m_chunksZ * Chunk::LENGTH;
		}
		
		[[nodiscard]] inline int chunksWidth() const
		{
			return m_chunksX;
		}
		
		[[nodiscard]] inline int chunksHeight() const
		{
			return m_chunksY;
		}
		
		[[nodiscard]] inline int chunksLength() const
		{
			return m_chunksZ;
		}
		
		[[nodiscard]] const Chunk& chunkAt(int cx, int cy, int cz);
		
		void addBlockChangeObserver(const Ownership<IHasBlockChangeCallback> &callback);
	};
}