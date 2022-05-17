//
// Created by cornchip on 4/28/22.
//

#pragma once

#include "Tuple3.h"

namespace Cosmos
{
	inline int flatten(int x, int y, int z, int width, int height)
	{
		return (z * width * height) + (y * width) + x;
	}
	
	inline Tuple3<int> expand(int i, int width, int height)
	{
		return Tuple3<int>(i % width, (i / width) % height, i / (width * height));
	}
}