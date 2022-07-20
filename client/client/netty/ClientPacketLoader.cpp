#include "ClientPacketLoader.h"

#include <iostream>
#include <cstring>

namespace Cosmos::Client::Netty
{
	void loadPackets(Cosmos::Netty::NettyRegistry& reg)
	{
		using namespace Cosmos::Netty;
		
		reg.registerType(PacketIdentifiers::ID_TEST, [](const PacketData& data, ENetPeer& sender, NettyRegistry& registry)
		{
			std::cout << "GOT A PACKET WITH TYPE " << PacketIdentifiers::ID_TEST << "!!!\nData: ";
			
			for(int i = 0; i < data.dataLength(); i++)
				std::cout << ((char*)data.dataConst())[i];
			std::cout << '\n';
			
			auto *toSendData = registry.createPacketData(sizeof("Hello From CB") - 1, PacketIdentifiers::ID_TEST);
			std::memcpy(toSendData->data(), "Hello From CB", sizeof("Hello From CB") - 1);
			
			registry.sendData(*toSendData, sender);
			
			registry.deletePacketData(toSendData);
		});
		
	}
}