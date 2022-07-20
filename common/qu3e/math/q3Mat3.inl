//--------------------------------------------------------------------------------------------------
// q3Mat3.inl
//
//	Copyright (c) 2014 Randy Gaul http://www.randygaul.net
//
//	This software is provided 'as-is', without any express or implied
//	warranty. In no event will the authors be held liable for any damages
//	arising from the use of this software.
//
//	Permission is granted to anyone to use this software for any purpose,
//	including commercial applications, and to alter it and redistribute it
//	freely, subject to the following restrictions:
//	  1. The origin of this software must not be misrepresented; you must not
//	     claim that you wrote the original software. If you use this software
//	     in a product, an acknowledgment in the product documentation would be
//	     appreciated but is not required.
//	  2. Altered server versions must be plainly marked as such, and must not
//	     be misrepresented as being the original software.
//	  3. This notice may not be removed or altered from any server distribution.
//--------------------------------------------------------------------------------------------------

namespace q3
{
//--------------------------------------------------------------------------------------------------
// q3Mat3
//--------------------------------------------------------------------------------------------------
	inline void q3Identity(q3Mat3 &m)
	{
		m.Set(
				float(1.0), float(0.0), float(0.0),
				float(0.0), float(1.0), float(0.0),
				float(0.0), float(0.0), float(1.0)
		);
	}

//--------------------------------------------------------------------------------------------------
	inline const q3Mat3 q3Rotate(const Vec3 &x, const Vec3 &y, const Vec3 &z)
	{
		return q3Mat3(x, y, z);
	}

//--------------------------------------------------------------------------------------------------
	inline const q3Mat3 q3Transpose(const q3Mat3 &m)
	{
		return q3Mat3(
				m.ex.x, m.ey.x, m.ez.x,
				m.ex.y, m.ey.y, m.ez.y,
				m.ex.z, m.ey.z, m.ez.z
		);
	}

//--------------------------------------------------------------------------------------------------
	inline void q3Zero(q3Mat3 &m)
	{
		memset(&m, 0, sizeof(float) * 9);
	}

//--------------------------------------------------------------------------------------------------
	inline const q3Mat3 q3Diagonal(float a)
	{
		return q3Mat3(
				float(a), float(0.0), float(0.0),
				float(0.0), float(a), float(0.0),
				float(0.0), float(0.0), float(a)
		);
	}

//--------------------------------------------------------------------------------------------------
	inline const q3Mat3 q3Diagonal(float a, float b, float c)
	{
		return q3Mat3(
				float(a), float(0.0), float(0.0),
				float(0.0), float(b), float(0.0),
				float(0.0), float(0.0), float(c)
		);
	}

//--------------------------------------------------------------------------------------------------
	inline const q3Mat3 q3OuterProduct(const Vec3 &u, const Vec3 &v)
	{
		Vec3 a = v * u.x;
		Vec3 b = v * u.y;
		Vec3 c = v * u.z;
		
		return q3Mat3(
				a.x, a.y, a.z,
				b.x, b.y, b.z,
				c.x, c.y, c.z
		);
	}

//--------------------------------------------------------------------------------------------------
	inline const q3Mat3 q3Covariance(Vec3 *points, u32 numPoints)
	{
		float invNumPoints = float(1.0) / float(numPoints);
		Vec3 c = Vec3(float(0.0), float(0.0), float(0.0));
		
		for (u32 i = 0; i < numPoints; ++i)
			c += points[i];
		
		c /= float(numPoints);
		
		float m00, m11, m22, m01, m02, m12;
		m00 = m11 = m22 = m01 = m02 = m12 = float(0.0);
		
		for (u32 i = 0; i < numPoints; ++i)
		{
			Vec3 p = points[i] - c;
			
			m00 += p.x * p.x;
			m11 += p.y * p.y;
			m22 += p.z * p.z;
			m01 += p.x * p.y;
			m02 += p.x * p.z;
			m12 += p.y * p.z;
		}
		
		float m01inv = m01 * invNumPoints;
		float m02inv = m02 * invNumPoints;
		float m12inv = m12 * invNumPoints;
		
		return q3Mat3(
				m00 * invNumPoints, m01inv, m02inv,
				m01inv, m11 * invNumPoints, m12inv,
				m02inv, m12inv, m22 * invNumPoints
		);
	};

//--------------------------------------------------------------------------------------------------
	inline const q3Mat3 q3Inverse(const q3Mat3 &m)
	{
		Vec3 tmp0, tmp1, tmp2;
		float detinv;
		
		tmp0 = q3Cross(m.ey, m.ez);
		tmp1 = q3Cross(m.ez, m.ex);
		tmp2 = q3Cross(m.ex, m.ey);
		
		detinv = float(1.0) / q3Dot(m.ez, tmp2);
		
		return q3Mat3(
				tmp0.x * detinv, tmp1.x * detinv, tmp2.x * detinv,
				tmp0.y * detinv, tmp1.y * detinv, tmp2.y * detinv,
				tmp0.z * detinv, tmp1.z * detinv, tmp2.z * detinv
		);
	}
}