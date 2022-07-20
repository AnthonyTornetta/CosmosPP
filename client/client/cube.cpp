//
// Created by cornchip on 4/28/22.
//
#include "cube.h"

#include <OgreManualObject.h>

namespace Cosmos::Rendering
{
	Cube::Cube(Tuple3<float> offset)
		: m_offset(offset)
	{
	
	}
	
	int Cube::addLeft(Ogre::ManualObject &man, int index, float scaleX, float scaleY, float scaleZ) const
	{
		man.position(m_offset.x + -0.5f * scaleX, m_offset.y + 0.5f * scaleY, m_offset.z + -0.5f * scaleZ);
		man.normal(-1, 0, 0);
		man.textureCoord(0, 0);
		
		man.position(m_offset.x + -0.5f * scaleX, m_offset.y + -0.5f * scaleY, m_offset.z + -0.5f * scaleZ);
		man.normal(-1, 0, 0);
		man.textureCoord(0, 1);
		
		man.position(m_offset.x + -0.5f * scaleX, m_offset.y + -0.5f * scaleY, m_offset.z + 0.5f * scaleZ);
		man.normal(-1, 0, 0);
		man.textureCoord(1, 1);
		
		man.position(m_offset.x + -0.5f * scaleX, m_offset.y + 0.5f * scaleY, m_offset.z + 0.5f * scaleZ);
		man.normal(-1, 0, 0);
		man.textureCoord(1, 0);
		
		man.quad(index, index + 1, index + 2, index + 3);
		
		return index + 4;
	}
	
	int Cube::addRight(Ogre::ManualObject &man, int index, float scaleX, float scaleY, float scaleZ) const
	{
		man.position(m_offset.x + 0.5f * scaleX, m_offset.y + 0.5f * scaleY, m_offset.z + 0.5f * scaleZ);
		man.normal(1, 0, 0);
		man.textureCoord(0, 0);
		
		man.position(m_offset.x + 0.5f * scaleX, m_offset.y + -0.5f * scaleY, m_offset.z + 0.5f * scaleZ);
		man.normal(1, 0, 0);
		man.textureCoord(0, 1);
		
		man.position(m_offset.x + 0.5f * scaleX, m_offset.y + -0.5f * scaleY, m_offset.z + -0.5f * scaleZ);
		man.normal(1, 0, 0);
		man.textureCoord(1, 1);
		
		man.position(m_offset.x + 0.5f * scaleX, m_offset.y + 0.5f * scaleY, m_offset.z + -0.5f * scaleZ);
		man.normal(1, 0, 0);
		man.textureCoord(1, 0);
		
		man.quad(index, index + 1, index + 2, index + 3);
		
		return index + 4;
	}
	
	int Cube::addTop(Ogre::ManualObject &man, int index, float scaleX, float scaleY, float scaleZ) const
	{
		man.position(m_offset.x + 0.5f * scaleX, m_offset.y + 0.5f * scaleY, m_offset.z + 0.5f * scaleZ);   // R F 1 0
		man.normal(0, 1, 0);
		man.textureCoord(1, 0);
		
		man.position(m_offset.x + 0.5f * scaleX, m_offset.y + 0.5f * scaleY, m_offset.z + -0.5f * scaleZ);  // R B 1 1
		man.normal(0, 1, 0);
		man.textureCoord(1, 1);
		
		man.position(m_offset.x + -0.5f * scaleX, m_offset.y + 0.5f * scaleY, m_offset.z + -0.5f * scaleZ); // L B 0 1
		man.normal(0, 1, 0);
		man.textureCoord(0, 1);
		
		man.position(m_offset.x + -0.5f * scaleX, m_offset.y + 0.5f * scaleY, m_offset.z + 0.5f * scaleZ); // L F 0 0
		man.normal(0, 1, 0);
		man.textureCoord(0, 0);
		
		man.quad(index, index + 1, index + 2, index + 3);
		
		return index + 4;
	}
	
	int Cube::addBottom(Ogre::ManualObject &man, int index, float scaleX, float scaleY, float scaleZ) const
	{
		man.position(m_offset.x + 0.5f * scaleX, m_offset.y + -0.5f * scaleY, m_offset.z + -0.5f * scaleZ);   // R F 1 0
		man.normal(0, -1, 0);
		man.textureCoord(1, 0);
		
		man.position(m_offset.x + 0.5f * scaleX, m_offset.y + -0.5f * scaleY, m_offset.z + 0.5f * scaleZ);  // R B 1 1
		man.normal(0, -1, 0);
		man.textureCoord(1, 1);
		
		man.position(m_offset.x + -0.5f * scaleX, m_offset.y + -0.5f * scaleY, m_offset.z + 0.5f * scaleZ); // L B 0 1
		man.normal(0, -1, 0);
		man.textureCoord(0, 1);
		
		man.position(m_offset.x + -0.5f * scaleX, m_offset.y + -0.5f * scaleY, m_offset.z + -0.5f * scaleZ); // L F 0 0
		man.normal(0, -1, 0);
		man.textureCoord(0, 0);
		
		man.quad(index, index + 1, index + 2, index + 3);
		
		return index + 4;
	}
	
	int Cube::addFront(Ogre::ManualObject &man, int index, float scaleX, float scaleY, float scaleZ) const
	{
		man.position(m_offset.x + -0.5f * scaleX, m_offset.y + 0.5f * scaleY, m_offset.z + 0.5f * scaleZ);
		man.normal(0, 0, 1);
		man.textureCoord(0, 0);
		
		man.position(m_offset.x + -0.5f * scaleX, m_offset.y + -0.5f * scaleY, m_offset.z + 0.5f * scaleZ);
		man.normal(0, 0, 1);
		man.textureCoord(0, 1);
		
		man.position(m_offset.x + 0.5f * scaleX, m_offset.y + -0.5f * scaleY, m_offset.z + 0.5f * scaleZ);
		man.normal(0, 0, 1);
		man.textureCoord(1, 1);
		
		man.position(m_offset.x + 0.5f * scaleX, m_offset.y + 0.5f * scaleY, m_offset.z + 0.5f * scaleZ);
		man.normal(0, 0, 1);
		man.textureCoord(1, 0);
		
		man.quad(index, index + 1, index + 2, index + 3);
		
		return index + 4;
	}
	
	int Cube::addBack(Ogre::ManualObject &man, int index, float scaleX, float scaleY, float scaleZ) const
	{
		man.position(m_offset.x + 0.5f * scaleX, m_offset.y + 0.5f * scaleY, m_offset.z + -0.5f * scaleZ);
		man.normal(0, 0, -1);
		man.textureCoord(0, 0);
		
		man.position(m_offset.x + 0.5f * scaleX, m_offset.y + -0.5f * scaleY, m_offset.z + -0.5f * scaleZ);
		man.normal(0, 0, -1);
		man.textureCoord(0, 1);
		
		man.position(m_offset.x + -0.5f * scaleX, m_offset.y + -0.5f * scaleY, m_offset.z + -0.5f * scaleZ);
		man.normal(0, 0, -1);
		man.textureCoord(1, 1);
		
		man.position(m_offset.x + -0.5f * scaleX, m_offset.y + 0.5f * scaleY, m_offset.z + -0.5f * scaleZ);
		man.normal(0, 0, -1);
		man.textureCoord(1, 0);
		
		man.quad(index, index + 1, index + 2, index + 3);
		
		return index + 4;
	}
}
