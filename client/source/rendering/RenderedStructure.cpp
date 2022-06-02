
#include "RenderedStructure.h"
#include <Ogre.h>
#include "../cube.h"

#include <ctime>
#include <string>
#include <source/ecs/component/ComponentIDs.h>
#include "source/structure/Structure.h"

namespace Cosmos::Rendering
{
	// TODO: not use time(0)
	RenderedStructure::RenderedStructure(Ogre::SceneManager& scnMgr,
										 Structure& structure)
		: m_scnMgr(scnMgr), m_manualObject(*scnMgr.createManualObject(std::to_string(time(nullptr)))), m_node(nullptr),
			m_structure(structure)
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
		
		for(auto &tuple : m_chunks)
		{
			Cosmos::Rendering::Cube cube({(float) tuple.x, (float) tuple.y, (float) tuple.z});
			
			cube.addBottom(m_manualObject,
						   cube.addTop(m_manualObject,
									   cube.addRight(m_manualObject,
													 cube.addLeft(m_manualObject,
																  cube.addBack(m_manualObject,
																			   cube.addFront(m_manualObject, 0))))));
		}
		
		m_chunks.clear();
	}
	
	void RenderedStructure::updateGL()
	{
		m_manualObject.end();
	}
	
	int RenderedStructure::STATIC_ID()
	{
		static int id = ComponentIDs::createID();
		
		return id;
	}
	
	int RenderedStructure::id() const
	{
		return STATIC_ID();
	}
	
	void RenderedStructure::addPlaceToUpdateNext(int chunkX, int chunkY, int chunkZ)
	{
		Tuple3<int> tuple(chunkX, chunkY, chunkZ);
		
		for(auto &t : m_chunks)
		{
			if(t == tuple)
				return;
		}
		
		m_chunks.push_back(tuple);
	}
	
	bool RenderedStructure::isAddedToScene() const
	{
		return m_node != nullptr;
	}
}
