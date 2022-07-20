//
// Created by cornchip on 6/1/22.
//

#pragma once

#include "source/ecs/component/Component.h"

namespace Cosmos::Rendering
{
	class DirtyNeedsRendered : public Component
	{
	private:
		const int m_chunkX, m_chunkY, m_chunkZ;
	
	public:
		DirtyNeedsRendered(int chunkX, int chunkY, int chunkZ);
		~DirtyNeedsRendered() override = default;
		
		[[nodiscard]] int id() const override;
		
		static int STATIC_ID();
		
		[[nodiscard]] bool canHaveDuplicates() const override;
		
		[[nodiscard]] int chunkX() const;
		[[nodiscard]] int chunkY() const;
		[[nodiscard]] int chunkZ() const;
	};
}
