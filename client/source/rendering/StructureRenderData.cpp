//
// Created by cornchip on 6/3/22.
//

#include "StructureRenderData.h"
#include "source/structure/Structure.h"
#include "source/utils/ArrayUtils.h"

namespace Cosmos::Rendering
{
	StructureRenderData::StructureRenderData(Structure &s, Ogre::SceneManager &mgr)
		: m_structure(s), m_chunksX(s.chunksWidth()), m_chunksY(s.chunksHeight()), m_chunksZ(s.chunksLength()),
		  m_renderData(new ChunkRenderData[s.chunksWidth() * s.chunksHeight() * s.chunksLength()]),
		  m_sceneNode(mgr.createSceneNode()), m_thread(nullptr)
	{
		for(int i = 0; i < s.chunksWidth() * s.chunksHeight() * s.chunksLength(); i++)
		{
			auto expanded = Cosmos::expand(i, s.chunksWidth(), s.chunksHeight());
			
			m_renderData[i].init(expanded.x, expanded.y, expanded.z, s, mgr, *m_sceneNode);
		}
	}
	
	StructureRenderData::~StructureRenderData()
	{
		if(m_thread)
			m_thread->join();
		
		m_sceneNode->removeAndDestroyAllChildren();
	}
	
	bool StructureRenderData::markBlockDirty(int x, int y, int z, const Block& old)
	{
		assert(Cosmos::within(x, y, z, m_chunksX * Chunk::WIDTH, m_chunksY * Chunk::HEIGHT, m_chunksZ * Chunk::LENGTH));
		
		if(m_structure.block(x, y, z) != old)
		{
			m_dirty.insert({x / Chunk::WIDTH, y / Chunk::HEIGHT, z / Chunk::LENGTH});
			return true;
		}
		
		return false;
	}
	
	bool StructureRenderData::update()
	{
		if(m_thread)
		{
			return false; // the thread is running, let it do its thing
		}
		
		if(!m_shouldUpdateGL.empty())
		{
			for (auto &pos: this->m_shouldUpdateGL)
			{
				m_renderData[Cosmos::flatten(pos.x, pos.y, pos.z, m_chunksX,
											 m_chunksY)].updateModelGL(m_structure);
			}
			
			m_shouldUpdateGL.clear();
			
			return false; // thread may still have more to add, so no return true
		}
		
		if(!m_dirty.empty())
		{
			m_thread = new std::thread([this]
		    {
				std::set<Tuple3<int>> copy = m_dirty;
				m_dirty.clear();
				
			   for (Tuple3<int> pos: copy)
			   {
				   m_renderData[Cosmos::flatten(pos.x, pos.y, pos.z, m_chunksX,
												m_chunksY)].updateModelNoGL(m_structure);
				
				   m_shouldUpdateGL.push_back(pos);
			   }

			   this->m_thread = nullptr;
		    });
			
			m_thread->detach();
			
			return false;
		}
		
		return true;
	}
}