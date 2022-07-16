//
// Created by cornchip on 7/14/22.
//

#include "PacketLoader.h"
#include "NettyRegistry.h"

#include <iostream>
#include <string>
#include <cstring>

namespace Cosmos::Netty
{
	void loadPackets(NettyRegistry& reg)
	{
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
