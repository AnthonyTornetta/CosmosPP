//
// Created by cornchip on 6/1/22.
//
//
// Created by cornchip on 6/1/22.
//

#pragma once

#include "source/ecs/component/Component.h"

namespace Cosmos::Rendering
{
	class NeedsOpenGLUpdated : public Component
	{
	public:
		NeedsOpenGLUpdated() = default;
		~NeedsOpenGLUpdated() override = default;
		
		[[nodiscard]] int id() const override;
		
		[[nodiscard]] static int STATIC_ID();
	};
}
