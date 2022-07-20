//
// Created by cornchip on 5/6/22.
//

#pragma once

#include "Renderable.h"
#include "source/ecs/component/Component.h"

#include "DirtyNeedsRendered.h"

#include "source/utils/Tuple3.h"

#include <vector>

namespace Ogre
{
	class ManualObject;
	class SceneNode;
}

namespace Cosmos
{
	class Structure;
}

namespace Cosmos::Rendering
{
	class RenderedStructure : public Renderable, public Component
	{
	public:
		Ogre::ManualObject& m_manualObject;
		Ogre::SceneManager& m_scnMgr;
		Ogre::SceneNode* m_node; // nullptr if not added to scene
		
		const Structure& m_structure;
		std::vector<Tuple3<int>> m_chunks;
	public:
		RenderedStructure(Ogre::SceneManager& m_scnMgr,
								   Structure& structure);
		
		~RenderedStructure() override;
		
		[[nodiscard]] int id() const override;
		
		static int STATIC_ID();
		
		void addPlaceToUpdateNext(int chunkX, int chunkY, int chunkZ);
		
		void updateNoGL() override;
		
		void updateGL() override;
		
		// Return null if something went wrong
		Ogre::SceneNode* addToScene() override;
		
		[[nodiscard]] bool isAddedToScene() const;
	};
}