//
// Created by cornchip on 7/17/22.
//

#pragma once
namespace Cosmos
{
	class Component
	{
	public:
		virtual ~Component() = 0;
		
		virtual int id() const = 0;
		
		static int generateID() {
			static int next_id = 0;
			
			return ++next_id;
		}
	};
}