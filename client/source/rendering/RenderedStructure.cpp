
#include "RenderedStructure.h"
#include <Ogre.h>
#include "../cube.h"

#include <time.h>
#include <string>

namespace Cosmos
{
	namespace Rendering
	{
		// TODO: not use time(0)
		RenderedStructure::RenderedStructure(Ogre::SceneManager& scnMgr)
			: m_scnMgr(scnMgr), m_manualObject(*scnMgr.createManualObject(std::to_string(time(0)))), m_node(nullptr)
		{
		
		}
		
		RenderedStructure::~RenderedStructure()
		{
			if(m_node)
			{
				m_scnMgr.destroySceneNode(m_node);
			}
		}
		
		Ogre::SceneNode* RenderedStructure::addToScene()
		{
			m_node = m_scnMgr.getRootSceneNode()->createChildSceneNode(Ogre::Vector3::ZERO, Ogre::Quaternion::IDENTITY);
			m_node->attachObject(&m_manualObject);
			
			return m_node;
		}
		
		void RenderedStructure::updateNoGL()
		{
			m_manualObject.begin("Examples/OgreLogo", Ogre::RenderOperation::OT_TRIANGLE_LIST);
			
			CosmosRendering::Cube cube;
			
			cube.addBottom(m_manualObject,
						   cube.addTop(m_manualObject,
									   cube.addRight(m_manualObject,
													 cube.addLeft(m_manualObject,
																  cube.addBack(m_manualObject,
																			   cube.addFront(m_manualObject, 0))))));
			
			
			
			
		}
		
		void RenderedStructure::updateGL()
		{
			m_manualObject.end();
		}
		
		bool RenderedStructure::needsUpdated()
		{
			return false;
		}
		
		void RenderedStructure::draw()
		{
		
		}
		
		Ogre::SceneNode *RenderedStructure::test()
		{
		return nullptr;
		}
	}
}