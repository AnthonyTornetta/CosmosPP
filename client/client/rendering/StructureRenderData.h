//
// Created by cornchip on 6/3/22.
//

#pragma once

#include <OgreManualObject.h>
#include "source/block/Block.h"
#include "ChunkRenderData.h"
#include "source/utils/Tuple3.h"
#include <thread>

namespace Cosmos
{
	class Structure;
	
	namespace Rendering
	{
		class StructureRenderData
		{
		private:
			// Dimensions for chunks
			int m_chunksX, m_chunksY, m_chunksZ;
			
			Structure& m_structure;
			
			ChunkRenderData* m_renderData;
			Ogre::SceneNode* m_sceneNode;
			
			std::set<Tuple3<int>> m_dirty;
			
			std::thread* m_thread;
			std::vector<Tuple3<int>> m_shouldUpdateGL;
		
		public:
			StructureRenderData(Structure &s, Ogre::SceneManager& mgr);
			~StructureRenderData();
			
			bool update();
			
			bool markBlockDirty(int x, int y, int z, const Block& old);
		};
	}
}