//
// Created by cornchip on 4/28/22.
//

#pragma once

#include "../block/Block.h"

#include "../ecs/component/Component.h"

namespace Cosmos
{
	class Chunk : public Component
	{
	public:
		static constexpr int WIDTH = 16;
		static constexpr int HEIGHT = 16;
		static constexpr int LENGTH = 16;
		
	private:
		/**
		 * This ID links to the block's id
		 */
		unsigned short* m_blocks;//[WIDTH * HEIGHT * LENGTH];
		
	public:
		Chunk();
		~Chunk() override;
		
		[[nodiscard]] int id() override;
		
		[[nodiscard]] static int STATIC_ID();
		
		/**
		 * Sets the block at the given ID.
		 * @param x The x [0, WIDTH)
		 * @param y The y [0, HEIGHT)
		 * @param z The z [0, LENGTH)
		 * @param b The block to change it to
		 */
		void blockAt(int x, int y, int z, const Block& b);
		
		/**
		 * Gets the block type at this location
		 * @param x [0, WIDTH)
		 * @param y [0, HEIGHT)
		 * @param z [0, LENGTH)
		 * @return The block type at this location
		 */
		[[nodiscard]] const Block& blockAt(int x, int y, int z) const;
		
		/**
		 * Checks if the coords are within the range [0, {WIDTH/HEIGHT/LENGTH})
		 * @param x Width check
		 * @param y Height check
		 * @param z Length check
		 * @return if the coords are within the range [0, {WIDTH/HEIGHT/LENGTH})
		 */
		[[nodiscard]] bool withinChunkCoords(int x, int y, int z) const;
		
		bool canHaveDuplicates() override;
	};
}
