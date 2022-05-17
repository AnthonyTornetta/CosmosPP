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
		inline static std::vector<Block> blocks = { };
		
	public:
		static const Block& getBlock(short id)
		{
			assert(id >= 0 && id < blocks.size());
			
			return blocks[id];
		}
		
		static void registerBlock(Block b)
		{
			blocks.push_back(b);
		}
	};
}