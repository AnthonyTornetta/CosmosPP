//
// Created by cornchip on 5/12/22.
//

#include "ComponentIDs.h"

namespace Cosmos
{
	int ComponentIDs::createID()
	{
		static int next_id = 0;
		
		return ++next_id;
	}
}