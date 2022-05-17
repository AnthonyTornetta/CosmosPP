//
// Created by cornchip on 4/28/22.
//

#pragma once

namespace Cosmos
{
	template<class T>
	class Tuple3
	{
	public:
		Tuple3(T x, T y, T z)
			: x(x), y(y), z(z)
		{
		
		}
		
		const T x, y, z;
	};
}