//
// Created by cornchip on 7/14/22.
//

#pragma once

#include "NettyRegistry.h"
#include <string>
#include <unordered_map>

namespace Cosmos::Netty
{
	class PacketIdentifiers
	{
	public:
		static inline const NettyRegistry::PacketIdentifier ID_TEST = (NettyRegistry::PacketIdentifier) (std::hash<std::string>()("cosmos:packet_test"));
	};
}