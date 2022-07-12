//
// Created by cornchip on 4/28/22.
//

#pragma once

#include <vector>

#include "Block.h"

#include <cassert>

namespace Cosmos
{
	class Blocks
	{
	private:
		inline static Block m_AIR{"cosmos:air"};
		inline static Block m_GRASS{"cosmos:grass"};
	
	public:
		inline static const Block& AIR = m_AIR;
		inline static const Block& GRASS = m_GRASS;
	
	private:
		// Make sure AIR's ID is always 0.
		inline static std::vector<const Block*> blocks = {};
		
	public:
		static const Block& getBlock(short id)
		{
			assert(id >= 0 && id < blocks.size());
			
			return *blocks[id];
		}
		
		static void registerBlock(Block& b)
		{
			b.id(blocks.size());
			blocks.push_back(&b);
		}
		
		static void registerDefaultBlocks()
		{
			registerBlock(m_AIR);
			registerBlock(m_GRASS);
		}
	};
}