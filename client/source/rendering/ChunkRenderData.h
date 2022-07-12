//
// Created by cornchip on 6/3/22.
//

#pragma once

#include <OgreManualObject.h>
#include <OgreSceneManager.h>
#include "source/block/Block.h"

namespace Cosmos
{
	class Structure;
	
	namespace Rendering
	{
		class ChunkRenderData
		{
		private:
			Ogre::ManualObject *m_manualObject;
			Ogre::SceneManager *m_sceneManager;
		
			int m_chunkX, m_chunkY, m_chunkZ;
			
		public:
			/**
			 * Empty so it can be initialized in a big array.  Use init() after creation.
			 */
			ChunkRenderData();
			~ChunkRenderData();
			
			void init(int chunkX, int chunkY, int chunkZ, const Structure &s, Ogre::SceneManager& mgr, Ogre::SceneNode& node);
			
			void updateModelNoGL(const Structure& s);
			void updateModelGL(const Structure& s);
		};
	}
}
