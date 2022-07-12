//
// Created by cornchip on 4/28/22.
//

#pragma once

#include "Tuple3.h"

namespace Cosmos
{
	[[nodiscard]] inline int flatten(int x, int y, int z, int width, int height)
	{
		return (z * width * height) + (y * width) + x;
	}
	
	[[nodiscard]] inline Tuple3<int> expand(int i, int width, int height)
	{
		return Tuple3<int>(i % width, (i / width) % height, i / (width * height));
	}
	
	[[nodiscard]] inline bool within(int x, int y, int z, int width, int height, int length)
	{
		return x >= 0 && x < width
			&& y >= 0 && y < height
			&& z >= 0 && z < length;
	}
}