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
		
		virtual Ogre::SceneNode* addToScene() = 0;
		
		virtual void updateNoGL() = 0;
		
		virtual void updateGL() = 0;
	};
}