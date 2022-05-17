//
// Created by cornchip on 5/12/22.
//

#include "../ecs/component/Component.h"

namespace Cosmos
{
	class Dirty : public Component
	{
	public:
		~Dirty() override;
		
		int id() override;
		
		static int STATIC_ID();
	};
}