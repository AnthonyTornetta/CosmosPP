//
// Created by cornchip on 5/6/22.
//

#pragma once

#include "Renderable.h"

namespace Ogre
{
	class ManualObject;
	class SceneNode;
}

namespace Cosmos
{
	namespace Rendering
	{
		class RenderedStructure : public Renderable
		{
		public:
			Ogre::ManualObject& m_manualObject;
			Ogre::SceneManager& m_scnMgr;
			Ogre::SceneNode* m_node; // nullptr if not added to scene
		
		public:
			RenderedStructure(Ogre::SceneManager& m_scnMgr);
			
			~RenderedStructure();
			
			void updateNoGL() override;
			
			void updateGL() override;
			
			bool needsUpdated() override;
			
			void draw() override;
			
			// Return null if something went wrong
			Ogre::SceneNode* addToScene() override;
			
			Ogre::SceneNode* test();
		};
	}
}