//
// Created by cornchip on 4/28/22.
//

#pragma once

#include "Chunk.h"

namespace Cosmos
{
	class Entity;
	
	/**
	 * Represents a collection of chunks
	 */
	class Structure : public Component
	{
	private:
		Chunk* m_chunks; // These are references to components - not owned by structure
		
		int m_chunksX, m_chunksY, m_chunksZ;
		
		Entity* m_entity;
		
		bool m_dirty;
	
	public:
		/**
		 * Represents a collection of chunks
		 * @param chunksX The number of chunks in the X direction
		 * @param chunksY The number of chunks in the Y direction
		 * @param chunksZ The number of chunks in the Z direction
		 */
		Structure(int chunksX, int chunksY, int chunksZ, Entity* entity);
		~Structure() override;
		
		bool withinBlocks(int x, int y, int z) const;
		
		[[nodiscard]] int id() const override;
		
		static int STATIC_ID();
		
		/**
		 * Gets the type of block where 0,0,0 is the left bottom back and right top front
		 * @param x [0, blocksWidth())
		 * @param y [0, blocksHeight())
		 * @param z [0, blocksLength())
		 * @return type of block at that location
		 */
		const Block& block(int x, int y, int z) const;
		
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
		inline bool dirty() const
		{
			return m_dirty;
		}
		
		inline int blocksWidth() const
		{
			return m_chunksX * Chunk::WIDTH;
		}
		
		inline int blocksHeight() const
		{
			return m_chunksY * Chunk::HEIGHT;
		}
		
		inline int blocksLength() const
		{
			return m_chunksZ * Chunk::LENGTH;
		}
	};
}