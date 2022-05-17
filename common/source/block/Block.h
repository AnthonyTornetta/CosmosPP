//
// Created by cornchip on 4/28/22.
//

#pragma once

#include <string>

namespace Cosmos
{
	class Block
	{
	private:
		unsigned short m_id;
		std::string m_block_name;
		
	public:
		Block(std::string block_name);
		
		virtual bool hasCollision() const;
		
		bool operator==(const Block& b) const;
		
		/**
		 * DO NOT CALL unless you know *exactly* what you're doing.
		 * @param id  The new ID to set the block to
		 */
		inline void id(unsigned short id)
		{
			m_id = id;
		}
		
		inline const std::string& blockName() const
		{
			return m_block_name;
		}
		
		/**
		 * ID used to identify this block from other blocks
		 * @return
		 */
		inline short id() const
		{
			return m_id;
		}
	};
}