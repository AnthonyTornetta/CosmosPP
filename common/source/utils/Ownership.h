//
// Created by cornchip on 7/17/22.
//

namespace Cosmos
{
	template<class T, bool isArray = false>
	class Ownership
	{
	private:
		T* m_data;
		bool m_owner;
		
	public:
		Ownership(T data, bool owner)
				: m_data(data), m_owner(owner)
		{
		
		}
		
		Ownership(const Ownership& o)
				: m_data(o.m_data), m_owner(o.m_owner)
		{
		
		}
		
		inline T* value()
		{
			return m_data;
		}
		
		[[nodiscard]] inline bool shouldDelete() const
		{
			return m_owner;
		}
		
		inline void revokeOwnership()
		{
			m_owner = false;
		}
		
		inline void makeOwner()
		{
			m_owner = true;
		}
		
		bool deleteIfOwner()
		{
			if(isArray && shouldDelete())
			{
				delete[] m_data;
				return true;
			}
			else if(!isArray && shouldDelete())
			{
				delete m_data;
				return true;
			}
			return false;
		}
	};
}