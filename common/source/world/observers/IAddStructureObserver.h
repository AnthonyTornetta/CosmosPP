//
// Created by cornchip on 7/17/22.
//

#pragma once

namespace Cosmos
{
	class CosmosWorld;
	class Structure;
	
	class IAddStructureObserver
	{
	public:
		IAddStructureObserver() = default;
		virtual ~IAddStructureObserver() = 0;
		
		/**
		 * Called whenever a structure is added to the world - return false to cancel the addition. The structure has not been added at the time of this calling
		 * @param world The world the structure was added to
		 * @param structure The structure that will be added to the world
		 * @return True if it should be added, false if not
		 */
		virtual bool onAddStructure(CosmosWorld& world, Structure& structure) = 0;
	};
}