//--------------------------------------------------------------------------------------------------
/**
@file	q3Box.cpp

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

#include "q3Box.h"
#include "../math/Vec3.h"

namespace q3
{
//--------------------------------------------------------------------------------------------------
// q3Box
//--------------------------------------------------------------------------------------------------
	bool q3Box::TestPoint(const q3Transform &tx, const Vec3 &p) const
	{
		q3Transform world = q3Mul(tx, local);
		Vec3 p0 = q3MulT(world, p);
		
		for (int i = 0; i < 3; ++i)
		{
			float d = p0[i];
			float ei = e[i];
			
			if (d > ei || d < -ei)
			{
				return false;
			}
		}
		
		return true;
	}

//--------------------------------------------------------------------------------------------------
	bool q3Box::Raycast(const q3Transform &tx, q3RaycastData *raycast) const
	{
		q3Transform world = q3Mul(tx, local);
		Vec3 d = q3MulT(world.rotation, raycast->dir);
		Vec3 p = q3MulT(world, raycast->start);
		const float epsilon = float(1.0e-8);
		float tmin = 0;
		float tmax = raycast->t;
		
		// t = (e[ i ] - p.[ i ]) / d[ i ]
		float t0;
		float t1;
		Vec3 n0;
		
		for (int i = 0; i < 3; ++i)
		{
			// Check for ray parallel to and outside of AABB
			if (q3Abs(d[i]) < epsilon)
			{
				// Detect separating axes
				if (p[i] < -e[i] || p[i] > e[i])
				{
					return false;
				}
			} else
			{
				float d0 = float(1.0) / d[i];
				float s = q3Sign(d[i]);
				float ei = e[i] * s;
				Vec3 n(0, 0, 0);
				n[i] = -s;
				
				t0 = -(ei + p[i]) * d0;
				t1 = (ei - p[i]) * d0;
				
				if (t0 > tmin)
				{
					n0 = n;
					tmin = t0;
				}
				
				tmax = q3Min(tmax, t1);
				
				if (tmin > tmax)
				{
					return false;
				}
			}
		}
		
		raycast->normal = q3Mul(world.rotation, n0);
		raycast->toi = tmin;
		
		return true;
	}

//--------------------------------------------------------------------------------------------------
	void q3Box::ComputeAABB(const q3Transform &tx, q3AABB *aabb) const
	{
		q3Transform world = q3Mul(tx, local);
		
		Vec3 v[8] = {
				Vec3(-e.x, -e.y, -e.z),
				Vec3(-e.x, -e.y, e.z),
				Vec3(-e.x, e.y, -e.z),
				Vec3(-e.x, e.y, e.z),
				Vec3(e.x, -e.y, -e.z),
				Vec3(e.x, -e.y, e.z),
				Vec3(e.x, e.y, -e.z),
				Vec3(e.x, e.y, e.z)
		};
		
		for (int i = 0; i < 8; ++i)
			v[i] = q3Mul(world, v[i]);
		
		Vec3 min(Q3_float_MAX, Q3_float_MAX, Q3_float_MAX);
		Vec3 max(-Q3_float_MAX, -Q3_float_MAX, -Q3_float_MAX);
		
		for (int i = 0; i < 8; ++i)
		{
			min = q3Min(min, v[i]);
			max = q3Max(max, v[i]);
		}
		
		aabb->min = min;
		aabb->max = max;
	}

//--------------------------------------------------------------------------------------------------
	void q3Box::ComputeMass(q3MassData *md) const
	{
		// Calculate inertia tensor
		float ex2 = float(4.0) * e.x * e.x;
		float ey2 = float(4.0) * e.y * e.y;
		float ez2 = float(4.0) * e.z * e.z;
		float mass = float(8.0) * e.x * e.y * e.z * density;
		float x = float(1.0 / 12.0) * mass * (ey2 + ez2);
		float y = float(1.0 / 12.0) * mass * (ex2 + ez2);
		float z = float(1.0 / 12.0) * mass * (ex2 + ey2);
		q3Mat3 I = q3Diagonal(x, y, z);
		
		// Transform tensor to local space
		I = local.rotation * I * q3Transpose(local.rotation);
		q3Mat3 identity;
		q3Identity(identity);
		I += (identity * q3Dot(local.position, local.position) - q3OuterProduct(local.position, local.position)) * mass;
		
		md->center = local.position;
		md->inertia = I;
		md->mass = mass;
	}

//--------------------------------------------------------------------------------------------------
	const int kBoxIndices[36] = {
			1 - 1, 7 - 1, 5 - 1,
			1 - 1, 3 - 1, 7 - 1,
			1 - 1, 4 - 1, 3 - 1,
			1 - 1, 2 - 1, 4 - 1,
			3 - 1, 8 - 1, 7 - 1,
			3 - 1, 4 - 1, 8 - 1,
			5 - 1, 7 - 1, 8 - 1,
			5 - 1, 8 - 1, 6 - 1,
			1 - 1, 5 - 1, 6 - 1,
			1 - 1, 6 - 1, 2 - 1,
			2 - 1, 6 - 1, 8 - 1,
			2 - 1, 8 - 1, 4 - 1
	};

//--------------------------------------------------------------------------------------------------
	void q3Box::Render(const q3Transform &tx, bool awake, q3Render *render) const
	{
		q3Transform world = q3Mul(tx, local);
		
		Vec3 vertices[8] = {
				Vec3(-e.x, -e.y, -e.z),
				Vec3(-e.x, -e.y, e.z),
				Vec3(-e.x, e.y, -e.z),
				Vec3(-e.x, e.y, e.z),
				Vec3(e.x, -e.y, -e.z),
				Vec3(e.x, -e.y, e.z),
				Vec3(e.x, e.y, -e.z),
				Vec3(e.x, e.y, e.z)
		};
		
		for (int i = 0; i < 36; i += 3)
		{
			Vec3 a = q3Mul(world, vertices[kBoxIndices[i]]);
			Vec3 b = q3Mul(world, vertices[kBoxIndices[i + 1]]);
			Vec3 c = q3Mul(world, vertices[kBoxIndices[i + 2]]);
			
			Vec3 n = q3Normalize(q3Cross(b - a, c - a));
			
			//render->SetPenColor( 0.2f, 0.4f, 0.7f, 0.5f );
			//render->SetPenPosition( a.x, a.y, a.z );
			//render->Line( b.x, b.y, b.z );
			//render->Line( c.x, c.y, c.z );
			//render->Line( a.x, a.y, a.z );
			
			render->SetTriNormal(n.x, n.y, n.z);
			render->Triangle(a.x, a.y, a.z, b.x, b.y, b.z, c.x, c.y, c.z);
		}
	}
}