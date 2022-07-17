//
// Created by cornchip on 7/17/22.
//

#pragma once

namespace Cosmos
{
	class CosmosWorld;
	class Structure;
	
	class IRemoveStructureObserver
	{
	public:
		IRemoveStructureObserver() = default;
		virtual ~IRemoveStructureObserver() = 0;
		
		/**
		 * Called whenever a structure is removed from the world - return false to cancel the removing. The structure has not been removed at the time of this calling
		 * @param world The world the structure was removed from
		 * @param structure The structure that will be removed from the world
		 * @return True if it should be removed, false if not
		 */
		virtual bool onRemoveStructure(CosmosWorld& world, Structure& structure) = 0;
	};
}