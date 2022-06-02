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
		
		bool operator==(const Tuple3<T> &t) const
		{
			return x == t.x && y == t.y && z == t.z;
		}
		
		bool operator!=(const Tuple3<T> &t) const
		{
			return x != t.x || y != t.y || z != t.z;
		}
		
		const T x, y, z;
	};
}