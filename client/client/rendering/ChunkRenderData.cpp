//
// Created by cornchip on 6/3/22.
//

#include "ChunkRenderData.h"
#include "source/structure/Structure.h"
#include "../cube.h"

#include <cassert>

namespace Cosmos::Rendering
{
	ChunkRenderData::ChunkRenderData()
		: m_manualObject(nullptr), m_sceneManager(nullptr)
	{
	
	}
	
	ChunkRenderData::~ChunkRenderData()
	{
		assert(m_manualObject);
		assert(m_sceneManager);
		
		m_sceneManager->destroyManualObject(m_manualObject);
	}
	
	void ChunkRenderData::init(int chunkX, int chunkY, int chunkZ, const Structure &s, Ogre::SceneManager &mgr, Ogre::SceneNode& node)
	{
		m_chunkX = chunkX;
		m_chunkY = chunkY;
		m_chunkZ = chunkZ;
		
		m_sceneManager = &mgr;
		m_manualObject = m_sceneManager->createManualObject();
		
		node.attachObject(m_manualObject);
	}
	
	void ChunkRenderData::updateModelNoGL(const Structure &s)
	{
		assert(m_manualObject);
		assert(m_sceneManager);
		
		m_manualObject->clear();
		
		m_manualObject->begin("Examples/OgreLogo", Ogre::RenderOperation::OT_TRIANGLE_LIST);
		
		for(int z = m_chunkZ * Chunk::LENGTH; z < (m_chunkZ + 1) * Chunk::LENGTH; z++)
		{
			for(int y = m_chunkY * Chunk::HEIGHT; y < (m_chunkY + 1) * Chunk::HEIGHT; y++)
			{
				for(int x = m_chunkX * Chunk::WIDTH; x < (m_chunkX + 1) * Chunk::WIDTH; x++)
				{
					Cube cube({(float)x, (float)y, (float)z});
					
					cube.addBottom(*m_manualObject,
						   cube.addTop(*m_manualObject,
									   cube.addRight(*m_manualObject,
													 cube.addLeft(*m_manualObject,
																  cube.addBack(*m_manualObject,
																			   cube.addFront(*m_manualObject, 0))))));
				}
			}
		}
	}
	
	void ChunkRenderData::updateModelGL(const Structure &s)
	{
		assert(m_manualObject);
		assert(m_sceneManager);
		
		m_manualObject->end();
	}
}