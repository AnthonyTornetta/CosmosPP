//
// Created by cornchip on 4/28/22.
//

#pragma once

namespace Ogre
{
	class ManualObject;
}

namespace CosmosRendering
{
	class Cube
	{
	public:
		int addLeft(Ogre::ManualObject &man, int index, float scaleX = 1, float scaleY = 1, float scaleZ = 1);
		int addRight(Ogre::ManualObject &man, int index, float scaleX = 1, float scaleY = 1, float scaleZ = 1);
		
		int addTop(Ogre::ManualObject &man, int index, float scaleX = 1, float scaleY = 1, float scaleZ = 1);
		int addBottom(Ogre::ManualObject &man, int index, float scaleX = 1, float scaleY = 1, float scaleZ = 1);
		
		int addFront(Ogre::ManualObject &man, int index, float scaleX = 1, float scaleY = 1, float scaleZ = 1);
		int addBack(Ogre::ManualObject &man, int index, float scaleX = 1, float scaleY = 1, float scaleZ = 1);
	};
}
