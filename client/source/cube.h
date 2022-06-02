//
// Created by cornchip on 4/28/22.
//

#pragma once

#include "source/utils/Tuple3.h"

namespace Ogre
{
	class ManualObject;
}

namespace Cosmos::Rendering
{
	class Cube
	{
	private:
		Tuple3<float> m_offset;
		
	public:
		explicit Cube(Tuple3<float> offset = {0, 0, 0});
		
		int addLeft(Ogre::ManualObject &man, int index, float scaleX = 1, float scaleY = 1, float scaleZ = 1) const;
		int addRight(Ogre::ManualObject &man, int index, float scaleX = 1, float scaleY = 1, float scaleZ = 1) const;
		
		int addTop(Ogre::ManualObject &man, int index, float scaleX = 1, float scaleY = 1, float scaleZ = 1) const;
		int addBottom(Ogre::ManualObject &man, int index, float scaleX = 1, float scaleY = 1, float scaleZ = 1) const;
		
		int addFront(Ogre::ManualObject &man, int index, float scaleX = 1, float scaleY = 1, float scaleZ = 1) const;
		int addBack(Ogre::ManualObject &man, int index, float scaleX = 1, float scaleY = 1, float scaleZ = 1) const;
	};
}
