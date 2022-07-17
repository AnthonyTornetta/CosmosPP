//
// Created by cornchip on 7/16/22.
//

#pragma once

#include "../../block/Block.h"
#include "../StructureBlock.h"

namespace Cosmos
{
	class IBlockUpdateObserver
	{
	public:
		virtual bool blockChanged(const Block& oldBlock, const Block& newBlock, StructureBlock& block) = 0;
	};
}