//
// Created by cornchip on 6/3/22.
//

#pragma once

namespace Cosmos
{
	class Structure;
	class Block;
	
	class IHasBlockChangeCallback
	{
	public:
		virtual ~IHasBlockChangeCallback() = default;
		
		virtual void onBlockUpdate(Structure& s, const Block& oldBlock, int x, int y, int z) = 0;
	};
}