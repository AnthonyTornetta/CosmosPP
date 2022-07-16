//
// Created by cornchip on 7/13/22.
//

#pragma once

#include <cstdint>
#include <map>

#include <enet/enet.h>

namespace Cosmos::Netty
{
	class PacketData
	{
	private:
		uint8_t* m_data;
		int writingIndex;
		const std::size_t m_dataLength;
		const bool m_freeMemory;
	
	public:
		/**
		 * Don't call this, use NettyRegistry#createPacketData instead.
		 * @param data
		 * @param dataLength
		 * @param writingAtIndex
		 * @param freeMemory
		 */
		PacketData(void* data, std::size_t dataLength, int writingAtIndex = 0, bool freeMemory = true)
				: m_dataLength(dataLength), m_data((uint8_t*)data), writingIndex(writingAtIndex), m_freeMemory(freeMemory)
		{
		
		}
		
		~PacketData()
		{
			if(m_freeMemory)
			{
				// This will not call any destructors
				delete[] ((uint8_t *) m_data);
			}
		}
		
		[[nodiscard]] void* data()
		{
			return ((uint8_t*)m_data) + writingIndex;
		}
		
		[[nodiscard]] void* fullData()
		{
			return m_data;
		}
		
		[[nodiscard]] const void* dataConst() const
		{
			return ((uint8_t*)m_data) + writingIndex;
		}
		
		[[nodiscard]] const void* fullDataConst() const
		{
			return m_data;
		}
		
		[[nodiscard]] size_t dataLength() const
		{
			return m_dataLength - writingIndex;
		}
		
		[[nodiscard]] size_t dataLengthFull() const
		{
			return m_dataLength;
		}
		
		void advanceWritingPosition(int pos)
		{
			writingIndex = pos;
		}
		
	};
	
	class NettyRegistry
	{
	public:
		typedef unsigned short PacketIdentifier;
		
		typedef void (*PacketCallback)(const PacketData& data, ENetPeer& sender, NettyRegistry& registry);
		
		static const inline PacketIdentifier INVALID_IDENTIFIER = 0;
		
	private:
		std::map<PacketIdentifier, PacketCallback> m_callbacks;
	
	public:
		void registerType(PacketIdentifier pid, PacketCallback callback);
		
		void runCallback(PacketIdentifier pid, const PacketData& data, ENetPeer& sender);
		
		PacketIdentifier extractIdentifier(const PacketData& data);
		
		static PacketIdentifier nextIdentifier();
		
		PacketData* createPacketData(size_t dataSize, PacketIdentifier identifier);
		PacketData* createPacketData(void* data, size_t dataSize);
		
		void deletePacketData(PacketData* data);
		
		void sendData(const PacketData& data, ENetPeer& toWho);
	};
}