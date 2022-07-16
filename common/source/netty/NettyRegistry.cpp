//
// Created by cornchip on 7/14/22.
//

#include "NettyRegistry.h"

#include <cassert>

namespace Cosmos::Netty
{
	void NettyRegistry::registerType(PacketIdentifier pid, PacketCallback callback)
	{
		m_callbacks[pid] = callback;
	}
	
	void NettyRegistry::runCallback(NettyRegistry::PacketIdentifier pid, const PacketData& data, ENetPeer& sender)
	{
		assert(m_callbacks.contains(pid)); // Die while debug mode to make sure only valid PIDs are sent
		
		if(!m_callbacks.contains(pid))
			return; // Do nothing in production if server receives invalid packet
			
		m_callbacks.at(pid)(data, sender, *this);
	}
	
	NettyRegistry::PacketIdentifier NettyRegistry::nextIdentifier()
	{
		static PacketIdentifier current = 0;
		
		return ++current;
	}
	
	NettyRegistry::PacketIdentifier NettyRegistry::extractIdentifier(const PacketData &data)
	{
		if(data.dataLengthFull() < sizeof(PacketIdentifier))
			return INVALID_IDENTIFIER;
		
		auto pid = PacketIdentifier((*(PacketIdentifier*)data.fullDataConst()));
		
		if(m_callbacks.contains(pid))
			return pid;
		else
			return INVALID_IDENTIFIER;
	}
	
	PacketData *NettyRegistry::createPacketData(size_t dataSize, PacketIdentifier id)
	{
		constexpr int size = sizeof(PacketIdentifier);
		
		auto data = new uint8_t[dataSize + size];
		((PacketIdentifier*)data)[0] = id;
		
		return new PacketData(data, dataSize + size, size);
	}
	
	PacketData *NettyRegistry::createPacketData(void *data, size_t dataSize)
	{
		return new PacketData(data, dataSize, sizeof(PacketIdentifier), false);
	}
	
	void NettyRegistry::sendData(const PacketData &data, ENetPeer& toWho)
	{
		ENetPacket * packet = enet_packet_create(data.fullDataConst(), data.dataLengthFull(), ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(&toWho, 0, packet);
	}
	
	void NettyRegistry::deletePacketData(PacketData *data)
	{
		delete data;
	}
}