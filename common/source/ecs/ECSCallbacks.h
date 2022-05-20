//
// Created by cornchip on 5/13/22.
//

#pragma once
namespace Cosmos
{
	class ECSWorld;
	class Entity;
	
	namespace ECSCallbacks
	{
		typedef void (*Callback)(const ECSWorld &world, const Entity &ent);
		typedef void (*CallbackMut)(ECSWorld &world, Entity &ent);
	}
}