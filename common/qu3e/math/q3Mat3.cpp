//--------------------------------------------------------------------------------------------------
/**
@file	q3Mat3.cpp

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
#include <complex>
#include "q3Mat3.h"

namespace q3
{
//--------------------------------------------------------------------------------------------------
// q3Mat3
//--------------------------------------------------------------------------------------------------
	q3Mat3::q3Mat3()
	{
	}

//--------------------------------------------------------------------------------------------------
	q3Mat3::q3Mat3(r32 a, r32 b, r32 c, r32 d, r32 e, r32 f, r32 g, r32 h, r32 i)
			: ex(a, b, c), ey(d, e, f), ez(g, h, i)
	{
	}

//--------------------------------------------------------------------------------------------------
	q3Mat3::q3Mat3(const Vec3 &_x, const Vec3 &_y, const Vec3 &_z)
			: ex(_x), ey(_y), ez(_z)
	{
	}

//--------------------------------------------------------------------------------------------------
	void q3Mat3::Set(r32 a, r32 b, r32 c, r32 d, r32 e, r32 f, r32 g, r32 h, r32 i)
	{
		ex.Set(a, b, c);
		ey.Set(d, e, f);
		ez.Set(g, h, i);
	}

//--------------------------------------------------------------------------------------------------
	void q3Mat3::Set(const Vec3 &axis, r32 angle)
	{
		r32 s = std::sin(angle);
		r32 c = std::cos(angle);
		r32 x = axis.x;
		r32 y = axis.y;
		r32 z = axis.z;
		r32 xy = x * y;
		r32 yz = y * z;
		r32 zx = z * x;
		r32 t = r32(1.0) - c;
		
		Set(
				x * x * t + c, xy * t + z * s, zx * t - y * s,
				xy * t - z * s, y * y * t + c, yz * t + x * s,
				zx * t + y * s, yz * t - x * s, z * z * t + c
		);
	}

//--------------------------------------------------------------------------------------------------
	void q3Mat3::SetRows(const Vec3 &x, const Vec3 &y, const Vec3 &z)
	{
		ex = x;
		ey = y;
		ez = z;
	}

//--------------------------------------------------------------------------------------------------
	q3Mat3 &q3Mat3::operator=(const q3Mat3 &rhs)
	{
		ex = rhs.ex;
		ey = rhs.ey;
		ez = rhs.ez;
		
		return *this;
	}

//--------------------------------------------------------------------------------------------------
	q3Mat3 &q3Mat3::operator*=(const q3Mat3 &rhs)
	{
		*this = *this * rhs;
		
		return *this;
	}

//--------------------------------------------------------------------------------------------------
	q3Mat3 &q3Mat3::operator*=(r32 f)
	{
		ex *= f;
		ey *= f;
		ez *= f;
		
		return *this;
	}


//--------------------------------------------------------------------------------------------------
	q3Mat3 &q3Mat3::operator+=(const q3Mat3 &rhs)
	{
		ex += rhs.ex;
		ey += rhs.ey;
		ez += rhs.ez;
		
		return *this;
	}

//--------------------------------------------------------------------------------------------------
	q3Mat3 &q3Mat3::operator-=(const q3Mat3 &rhs)
	{
		ex -= rhs.ex;
		ey -= rhs.ey;
		ez -= rhs.ez;
		
		return *this;
	}

//--------------------------------------------------------------------------------------------------
	Vec3 &q3Mat3::operator[](u32 index)
	{
		switch (index)
		{
			case 0:
				return ex;
			case 1:
				return ey;
			case 2:
				return ez;
			default:
				assert(false);
				return ex;
		}
	}

//--------------------------------------------------------------------------------------------------
	const Vec3 &q3Mat3::operator[](u32 index) const
	{
		switch (index)
		{
			case 0:
				return ex;
			case 1:
				return ey;
			case 2:
				return ez;
			default:
				assert(false);
				return ex;
		}
	}

//--------------------------------------------------------------------------------------------------
	const Vec3 q3Mat3::Column0() const
	{
		return Vec3(ex.x, ey.x, ez.x);
	}

//--------------------------------------------------------------------------------------------------
	const Vec3 q3Mat3::Column1() const
	{
		return Vec3(ex.y, ey.y, ez.y);
	}

//--------------------------------------------------------------------------------------------------
	const Vec3 q3Mat3::Column2() const
	{
		return Vec3(ex.z, ey.z, ez.z);
	}

//--------------------------------------------------------------------------------------------------
	const Vec3 q3Mat3::operator*(const Vec3 &rhs) const
	{
		return Vec3(
				ex.x * rhs.x + ey.x * rhs.y + ez.x * rhs.z,
				ex.y * rhs.x + ey.y * rhs.y + ez.y * rhs.z,
				ex.z * rhs.x + ey.z * rhs.y + ez.z * rhs.z
		);
	}

//--------------------------------------------------------------------------------------------------
	const q3Mat3 q3Mat3::operator*(const q3Mat3 &rhs) const
	{
		return q3Mat3(
				(*this * rhs.ex),
				(*this * rhs.ey),
				(*this * rhs.ez)
		);
	}

//--------------------------------------------------------------------------------------------------
	const q3Mat3 q3Mat3::operator*(r32 f) const
	{
		return q3Mat3(ex * f, ey * f, ez * f);
	}

//--------------------------------------------------------------------------------------------------
	const q3Mat3 q3Mat3::operator+(const q3Mat3 &rhs) const
	{
		return q3Mat3(ex + rhs.ex, ey + rhs.ey, ez + rhs.ez);
	}

//--------------------------------------------------------------------------------------------------
	const q3Mat3 q3Mat3::operator-(const q3Mat3 &rhs) const
	{
		return q3Mat3(ex - rhs.ex, ey - rhs.ey, ez - rhs.ez);
	}
}