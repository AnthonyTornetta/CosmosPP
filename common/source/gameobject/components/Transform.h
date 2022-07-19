//
// Created by cornchip on 7/19/22.
//

#pragma once

#include "qu3e/q3.h"
#include "../Component.h"

namespace Cosmos
{
	class Transform : public Component
	{
	public:
		Transform() = default;
		~Transform() override = default;
		
		
		
		int id() const override
		{
			static int s_id = Component::generateID();
			
			return s_id;
		}
	};
}