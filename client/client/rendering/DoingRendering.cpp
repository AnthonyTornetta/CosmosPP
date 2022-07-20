//
// Created by cornchip on 6/1/22.
//
#include <source/ecs/component/ComponentIDs.h>
#include "DoingRendering.h"

namespace Cosmos::Rendering
{
	int DoingRendering::STATIC_ID()
	{
		static int id = ComponentIDs::createID();
		
		return id;
	}
	
	int DoingRendering::id() const
	{
		return STATIC_ID();
	}
	
	Rendering::DoingRendering::DoingRendering(std::thread *renderingThread)
		: m_renderingThread(renderingThread)
	{
	
	}
}