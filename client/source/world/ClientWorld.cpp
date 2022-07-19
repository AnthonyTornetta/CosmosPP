//
// Created by cornchip on 6/2/22.
//
#include "source/block/Block.h"
#include "source/structure/Structure.h"
#include "ClientWorld.h"
#include "source/utils/Ownership.h"

namespace Cosmos
{
	ClientWorld::ClientWorld(Ogre::SceneManager* mgr)
			: m_sceneManager(mgr)
	{
	
	}
	
	void ClientWorld::update()
	{
		CosmosWorld::update();
	}
	
	void ClientWorld::onBlockUpdate(Structure& s, const Block& oldBlock, int x, int y, int z)
	{
		printf("BLOCK CHANGED!\n");
		
		auto &renderData = m_renderData.at(0); // TODO: 0 is meant to be the structure's ID
		
		if(renderData.markBlockDirty(x, y, z, oldBlock))
		{
			m_needsRendered.insert(&renderData);
		}
	}
	
	void ClientWorld::addStructure(Structure *s)
	{
		CosmosWorld::addStructure(s);
		
		m_renderData.insert({0, Cosmos::Rendering::StructureRenderData(*s, *m_sceneManager)});
		
		s->addBlockChangeObserver(Ownership<IHasBlockChangeCallback>(this, false));
	}
	
	void ClientWorld::updateRenderData()
	{
		std::set<Rendering::StructureRenderData*> newData;
		
		for(auto *x : m_needsRendered)
		{
			if(!x->update())
			{
				newData.insert(x);
			}
		}
		
		m_needsRendered = std::move(newData);
	}
}