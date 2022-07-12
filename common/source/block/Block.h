//
// Created by cornchip on 4/28/22.
//

#pragma once

#include <string>

#include <cassert>

namespace Cosmos
{
	class Block
	{
	private:
		unsigned short m_id;
		std::string m_block_name;
		
		// Prevents a block from being copied by accident
		Block(const Block& b)
			: m_id(-1)
		{
			assert(false);
		}
		
		// Prevents a block from being copied by accident
		Block& operator=(const Block& temp_obj)
		{
			assert(false);
		}
		
	public:
		explicit Block(std::string block_name);
		
		[[nodiscard]] virtual bool hasCollision() const;
		
		bool operator==(const Block& b) const;
		
		bool operator!=(const Block& b) const;
		
		/**
		 * DO NOT CALL unless you know *exactly* what you're doing.
		 * @param id  The new ID to set the block to
		 */
		inline void id(unsigned short id)
		{
			m_id = id;
		}
		
		[[nodiscard]] inline const std::string& blockName() const
		{
			return m_block_name;
		}
		
		/**
		 * ID used to identify this block from other blocks
		 * @return
		 */
		[[nodiscard]] inline unsigned short id() const
		{
			return m_id;
		}
	};
}