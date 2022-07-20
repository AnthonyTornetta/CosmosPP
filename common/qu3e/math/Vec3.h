//--------------------------------------------------------------------------------------------------
/**
@file	Vec3.h

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

#ifndef Vec3_H
#define Vec3_H

#include "../common/q3Types.h"

namespace q3
{
	float q3Abs(float a);
	
	float q3Min(float a, float b);
	
	float q3Max(float a, float b);

//--------------------------------------------------------------------------------------------------
// Vec3
//--------------------------------------------------------------------------------------------------
	struct Vec3
	{
		union
		{
			float v[3];
			
			struct
			{
				float x;
				float y;
				float z;
			};
		};
		
		Vec3();
		
		Vec3(float _x, float _y, float _z);
		
		void Set(float _x, float _y, float _z);
		
		void SetAll(float a);
		
		Vec3 &operator+=(const Vec3 &rhs);
		
		Vec3 &operator-=(const Vec3 &rhs);
		
		Vec3 &operator*=(float f);
		
		Vec3 &operator/=(float f);
		
		float &operator[](u32 i);
		
		float operator[](u32 i) const;
		
		Vec3 operator-(void) const;
		
		const Vec3 operator+(const Vec3 &rhs) const;
		
		const Vec3 operator-(const Vec3 &rhs) const;
		
		const Vec3 operator*(float f) const;
		
		const Vec3 operator/(float f) const;
	};
}

#include "Vec3.inl"

#endif // Vec3_H
