//--------------------------------------------------------------------------------------------------
/**
@file	q3Mat3.h

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
	  2. Altered server versions must be plainly marked as such, and must not
	     be misrepresented as being the original software.
	  3. This notice may not be removed or altered from any server distribution.
*/
//--------------------------------------------------------------------------------------------------

#ifndef Q3MAT3_H
#define Q3MAT3_H

#include <cstring>	// memset
#include "../common/q3Types.h"
#include "Vec3.h"

namespace q3
{
//--------------------------------------------------------------------------------------------------
// q3Mat3
//--------------------------------------------------------------------------------------------------
	struct q3Mat3
	{
		Vec3 ex;
		Vec3 ey;
		Vec3 ez;
		
		q3Mat3();
		
		q3Mat3(float a, float b, float c, float d, float e, float f, float g, float h, float i);
		
		q3Mat3(const Vec3 &_x, const Vec3 &_y, const Vec3 &_z);
		
		void Set(float a, float b, float c, float d, float e, float f, float g, float h, float i);
		
		void Set(const Vec3 &axis, float angle);
		
		void SetRows(const Vec3 &x, const Vec3 &y, const Vec3 &z);
		
		q3Mat3 &operator=(const q3Mat3 &rhs);
		
		q3Mat3 &operator*=(const q3Mat3 &rhs);
		
		q3Mat3 &operator*=(float f);
		
		q3Mat3 &operator+=(const q3Mat3 &rhs);
		
		q3Mat3 &operator-=(const q3Mat3 &rhs);
		
		Vec3 &operator[](u32 index);
		
		const Vec3 &operator[](u32 index) const;
		
		const Vec3 Column0() const;
		
		const Vec3 Column1() const;
		
		const Vec3 Column2() const;
		
		const Vec3 operator*(const Vec3 &rhs) const;
		
		const q3Mat3 operator*(const q3Mat3 &rhs) const;
		
		const q3Mat3 operator*(float f) const;
		
		const q3Mat3 operator+(const q3Mat3 &rhs) const;
		
		const q3Mat3 operator-(const q3Mat3 &rhs) const;
	};
}

#include "q3Mat3.inl"

#endif // Q3MAT3_H
