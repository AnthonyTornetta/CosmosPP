//
// Created by cornchip on 6/1/22.
//

#include <source/ecs/component/ComponentIDs.h>
#include "NeedsOpenGLUpdated.h"

namespace Cosmos::Rendering
{
	int NeedsOpenGLUpdated::id() const
	{
		return STATIC_ID();
	}
	
	int NeedsOpenGLUpdated::STATIC_ID()
	{
		static int id = ComponentIDs::createID();
		
		return id;
	}
}