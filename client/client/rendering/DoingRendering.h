//
// Created by cornchip on 6/1/22.
//

#pragma once

#include "source/ecs/component/Component.h"
#include <thread>

namespace Cosmos::Rendering
{
	class DoingRendering : public Component
	{
	private:
		std::thread *m_renderingThread;
	
	public:
		explicit DoingRendering(std::thread *renderingThread);
		
		~DoingRendering() override = default;
		
		[[nodiscard]] int id() const override;
		
		static int STATIC_ID();
		
		[[nodiscard]] std::thread *thread()
		{
			return m_renderingThread;
		}
	};
}