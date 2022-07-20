//
// Created by cornchip on 7/19/22.
//

#pragma once

#include "source/netty/PacketLoader.h"
#include "source/netty/NettyRegistry.h"

namespace Cosmos::Server::Netty
{
	void loadPackets(Cosmos::Netty::NettyRegistry& registry);
}
