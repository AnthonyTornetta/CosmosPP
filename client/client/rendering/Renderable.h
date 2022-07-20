//
// Created by cornchip on 5/6/22.
//

#pragma once

namespace Ogre
{
	class SceneManager;
	class SceneNode;
}

namespace Cosmos::Rendering
{
	class Renderable
	{
	public:
		Renderable() = default;
		
		~Renderable() = default;
		
		/**
		 * Returns the SceneNode to be used for this
		 * @return the SceneNode to be used for this
		 */
		virtual Ogre::SceneNode* addToScene() = 0;
		
		/**
		 * Rendering stuff that can be done on a separate thread
		 */
		virtual void updateNoGL() = 0;
		
		/**
		 * Rendering stuff that has to be done on the main thread
		 */
		virtual void updateGL() = 0;
	};
}