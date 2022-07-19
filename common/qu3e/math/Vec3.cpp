//--------------------------------------------------------------------------------------------------
/**
@file	Vec3.cpp

@author	Randy Gaul
@date	10/10/2014

	Copyright (c) 2014 Randy Gaul http://www.randygaul.net

	This software is provided 'as-is', without any express or implied
	warranty. In no event will the authors be held liable for any damages
	arising from the use of this software.

	Permission is granted to anyone to use this software for any purpose,
	including commercial applications, and to alter it and redistribute it
	freely, subject to the following restrictions:
	  1. The origin of this software must not be misrepresented; you must not
	     claim that you wrote the original software. If you use this software
	     in a product, an acknowledgment in the product documentation would be
	     appreciated but is not required.
	  2. Altered source versions must be plainly marked as such, and must not
	     be misrepresented as being the original software.
	  3. This notice may not be removed or altered from any source distribution.
*/
//--------------------------------------------------------------------------------------------------

#include <cassert>
#include "Vec3.h"

namespace q3
{
//--------------------------------------------------------------------------------------------------
// Vec3
//--------------------------------------------------------------------------------------------------
	Vec3::Vec3()
	{
	}

//--------------------------------------------------------------------------------------------------
	Vec3::Vec3(r32 _x, r32 _y, r32 _z)
			: x(_x), y(_y), z(_z)
	{
	}

//--------------------------------------------------------------------------------------------------
	void Vec3::Set(r32 _x, r32 _y, r32 _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

//--------------------------------------------------------------------------------------------------
	void Vec3::SetAll(r32 a)
	{
		x = a;
		y = a;
		z = a;
	}

//--------------------------------------------------------------------------------------------------
	Vec3 &Vec3::operator+=(const Vec3 &rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		
		return *this;
	}

//--------------------------------------------------------------------------------------------------
	Vec3 &Vec3::operator-=(const Vec3 &rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		
		return *this;
	}

//--------------------------------------------------------------------------------------------------
	Vec3 &Vec3::operator*=(r32 f)
	{
		x *= f;
		y *= f;
		z *= f;
		
		return *this;
	}

//--------------------------------------------------------------------------------------------------
	Vec3 &Vec3::operator/=(r32 f)
	{
		x /= f;
		y /= f;
		z /= f;
		
		return *this;
	}

//--------------------------------------------------------------------------------------------------
	r32 &Vec3::operator[](u32 i)
	{
		assert(i >= 0 && i < 3);
		
		return v[i];
	}

//--------------------------------------------------------------------------------------------------
	r32 Vec3::operator[](u32 i) const
	{
		assert(i >= 0 && i < 3);
		
		return v[i];
	}

//--------------------------------------------------------------------------------------------------
	Vec3 Vec3::operator-(void) const
	{
		return Vec3(-x, -y, -z);
	}

//--------------------------------------------------------------------------------------------------
	const Vec3 Vec3::operator+(const Vec3 &rhs) const
	{
		return Vec3(x + rhs.x, y + rhs.y, z + rhs.z);
	}

//--------------------------------------------------------------------------------------------------
	const Vec3 Vec3::operator-(const Vec3 &rhs) const
	{
		return Vec3(x - rhs.x, y - rhs.y, z - rhs.z);
	}

//--------------------------------------------------------------------------------------------------
	const Vec3 Vec3::operator*(r32 f) const
	{
		return Vec3(x * f, y * f, z * f);
	}

//--------------------------------------------------------------------------------------------------
	const Vec3 Vec3::operator/(r32 f) const
	{
		return Vec3(x / f, y / f, z / f);
	}

//--------------------------------------------------------------------------------------------------
	const Vec3 operator*(r32 f, const Vec3 &rhs)
	{
		return Vec3(rhs.x * f, rhs.y * f, rhs.z * f);
	}
}