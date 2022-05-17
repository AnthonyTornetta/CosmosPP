//
// Created by cornchip on 5/6/22.
//

#pragma once

namespace Ogre
{
	class SceneManager;
	class SceneNode;
}

namespace Cosmos
{
	namespace Rendering
	{
		class Renderable
		{
		public:
			Renderable() = default;
			
			~Renderable() = default;
			
			virtual Ogre::SceneNode* addToScene() = 0;
			
			virtual void updateNoGL() = 0;
			
			virtual void updateGL() = 0;
			
			virtual bool needsUpdated() = 0;
			
			/**
			 * Renders this object to the screen
			 */
			virtual void draw() = 0;
		};
	}
}