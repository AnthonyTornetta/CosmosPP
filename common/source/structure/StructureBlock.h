//
// Created by cornchip on 7/16/22.
//

#pragma once

namespace Cosmos
{
	class Block;
	class Structure;
	
	class StructureBlock
	{
	private:
		const int m_x, m_y, m_z;
		Structure& m_structure;
		
	public:
		StructureBlock(int x, int y, int z, Structure& s);
		
		[[nodiscard]] const Block& block() const;
		
		void block(const Block& block);
		
		[[nodiscard]] inline int x() const
		{
			return m_x;
		};
		
		[[nodiscard]] inline int y() const
		{
			return m_y;
		};
		
		[[nodiscard]] inline int z() const
		{
			return m_z;
		};
	};
}