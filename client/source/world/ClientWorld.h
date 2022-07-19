//
// Created by cornchip on 6/2/22.
//

#include <map>
#include "source/world/CosmosWorld.h"
#include "source/structure/IHasBlockChangeCallback.h"

#include "../rendering/StructureRenderData.h"

#pragma once

namespace Cosmos
{
	class ClientWorld : public CosmosWorld, public IHasBlockChangeCallback
	{
	private:
		std::map<int, Rendering::StructureRenderData> m_renderData;
		
		std::set<Rendering::StructureRenderData*> m_needsRendered;
		
		Ogre::SceneManager* m_sceneManager;
		
	public:
		ClientWorld(Ogre::SceneManager* mgr);
		~ClientWorld() override = default;
		
		void update() override;
		
		void updateRenderData();
		
		void onBlockUpdate(Structure& s, const Block& oldBlock, int x, int y, int z) override;
		
		void addStructure(Structure* s) override;
	};
}