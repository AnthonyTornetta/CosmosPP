//
// Created by cornchip on 4/28/22.
//

#include <iostream>

#include <qu3e/q3.h>
#include <chrono>
#include <string>
#include <thread>

#include <enet/enet.h>
#include <atomic>
#include <sstream>
#include <vector>

#include "source/netty/Constants.h"

struct Tuple2
{
	int x, y;
};

class ReferenceString
{
	// [start, end)
	const int start, end;
	const std::string& stringRef;

public:
	ReferenceString(size_t start, size_t end, const std::string& str)
		: start(start), end(end), stringRef(str)
	{
	
	}
	
	char operator[](int i) const
	{
		assert(i + start < end);
		return stringRef[i + start];
	}
	
	size_t size() const
	{
		return end - start;
	}
	
	bool operator==(const std::string& str) const
	{
		if(size() != str.size())
			return false;
		for(int i = 0; i < size(); i++)
			if(str[i] != (*this)[i])
				return false;
		return true;
	}
	
	bool operator==(const ReferenceString& str) const
	{
		if(size() != str.size())
			return false;
		for(int i = 0; i < size(); i++)
			if(str[i] != (*this)[i])
				return false;
		return true;
	}
};

std::vector<ReferenceString> split(const std::string& str, const char on)
{
	std::vector<ReferenceString> vec;
	
	Tuple2 working {-1, -1};
	
	for(int i = 0; i < str.size(); i++)
	{
		if(str[i] == on)
		{
			if(working.x != -1)
			{
				working.y = i;
				vec.emplace_back(working.x, working.y, str);
				working.x = -1;
				working.y = -1;
			}
		}
		else if(working.x == -1)
		{
			working.x = i;
		}
	}
	
	if(working.x != -1)
	{
		working.y = (int)str.size();
		vec.emplace_back(working.x, working.y, str);
	}
	
	return vec;
}

void sendPacket(ENetPeer* peer, const void* data, size_t data_size)
{
	ENetPacket * packet = enet_packet_create(data, data_size, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
}

#include "source/netty/NettyRegistry.h"
#include "server/netty/ServerPacketLoader.h"

int main()
{
	using namespace Cosmos::Netty;
	using namespace Cosmos::Server::Netty;
	NettyRegistry registry;
	
	loadPackets(registry);
	
	std::atomic_bool isRunning{true};
	
	std::vector<ENetPeer*> peers;
	
	std::thread console([&]()
	{
		std::string line;
		while (isRunning)
		{
			std::cout << "> ";
			std::getline(std::cin, line);
			if (line == "exit")
			{
				isRunning = false;
			}
			else if(line == "help")
			{
				std::cout << "exit - Stop execution.\n";
			}
			else
			{
				auto aroundSpaces = split(line, ' ');
				
				if(!aroundSpaces.empty())
				{
					if(aroundSpaces[0] == "say")
					{
						int textStart = 4;
						
						std::cout << &line.c_str()[textStart] << '\n';
						
						PacketData* pdata = registry.createPacketData(line.size() - 3, Cosmos::Netty::PacketIdentifiers::ID_TEST);
						
						std::memcpy(pdata->data(), &line.c_str()[textStart], line.size() - 3);
						
						for(auto *peer: peers)
						{
							registry.sendData(*pdata, *peer);
						}
						
						registry.deletePacketData(pdata);
					}
					else
					{
						std::cout << "Unknown command, type help for help.\n";
					}
				}
			}
		}
	});
	
	if (enet_initialize() != 0)
	{
		std::cerr << "Something went wrong initializing ENet.\n";
		return EXIT_FAILURE;
	}
	
	// de-initializes enet when the program closes
	atexit(enet_deinitialize);
	
	ENetAddress address;
	ENetHost *server;
	
	address.host = ENET_HOST_ANY;
	address.port = Cosmos::Netty::DEFAULT_PORT;
	
	// http://enet.bespin.org/Tutorial.html
	// 32 clients, 8 channels, 0 = assume any incoming bandwidth, 0 = assume any outgoing bandwidth
	server = enet_host_create(&address, 32, 8, 0, 0);
	
	if (!server)
	{
		std::cerr << "Error creating ENet server.  Make sure that port is free.\n";
		return EXIT_FAILURE;
	}
	
	
	while(isRunning)
	{
		ENetEvent event;
		
		while(enet_host_service(server, &event, 1000) > 0)
		{
			switch(event.type)
			{
				case ENET_EVENT_TYPE_CONNECT:
				{
					event.peer->data = (enet_uint8 *)"FirstConnection";
					printf("A new client has connected! {%x}:{%u} Named {%s}\n",
						   event.peer->address.host,
						   event.peer->address.port,
						   (char*)event.peer->data);
					
					
					peers.push_back(event.peer);
					
					break;
				}
				case ENET_EVENT_TYPE_RECEIVE:
				{
					if(event.packet->dataLength > 0)
					{
						PacketData* data = registry.createPacketData(event.packet->data, event.packet->dataLength);
						
						auto pid = registry.extractIdentifier(*data);
						if(pid != NettyRegistry::INVALID_IDENTIFIER)
						{
							registry.runCallback(pid, *data, *event.peer);
						}
						else
						{
							std::cerr << "Invalid Packet Identifier Received: " << pid << '\n';
						}
						
						registry.deletePacketData(data);
					}
					
					enet_packet_destroy(event.packet);
					
//					sendPacket(event.peer, "Got your message!", strlen("Got your message!") + 1);
					
					break;
				}
				case ENET_EVENT_TYPE_DISCONNECT:
				{
					printf("%s disconnected\n", (char*)event.peer->data);
					for(int i = 0; i < peers.size(); i++)
					{
						if(peers[i] == event.peer)
						{
							peers.erase(peers.begin() + i);
							break;
						}
					}
					event.peer->data = nullptr;
				}
				default:
					break;
			}
		}
	}
	
	enet_host_destroy(server);

//	using namespace q3;
//
//	q3Scene scene(1 / 60.0f);
//
//	q3::q3BodyDef bdef;
//	bdef.position = q3::q3Vec3(0, 10, -20);
//	bdef.bodyType = q3::eDynamicBody;
//
//	q3::q3BodyDef plane;
//	plane.position = q3::q3Vec3(2.5, -10, -20);
//	plane.bodyType = q3::eStaticBody;
//
//	q3Body *mainBody = scene.CreateBody(bdef);
//	q3Body *planeBody = scene.CreateBody(plane);
//
//	q3::q3BoxDef boxDef;
//	q3Transform trans;
//	trans.position.Set(0, 0, 0);
//	trans.rotation.Set(1, 0, 0, 0, 1, 0, 0, 0, 1);
//	boxDef.Set(trans, {1, 1, 1});
//	boxDef.SetRestitution(0.1);
//	mainBody->AddBox(boxDef);
//
//	q3Transform trans2;
//	trans2.position.Set(0, 0, 0);
//	trans2.rotation.Set(1, 0, 0, 0, 1, 0, 0, 0, 1);
//	q3::q3BoxDef planeBox;
//	planeBox.Set(trans2, {5, 5, 5});
//	planeBox.SetRestitution(0.1);
//	planeBody->AddBox(planeBox);
//
//	auto last = std::chrono::system_clock::now();
//
//	while (true)
//	{
//		auto now = std::chrono::system_clock::now();
//
//		if (now - last < std::chrono::milliseconds(16))
//		{
//			std::this_thread::sleep_for(std::chrono::milliseconds(16) - (now - last));
//		}
//
//		scene.Step();
//
//		std::cout << mainBody->GetTransform().position.x << ", " << mainBody->GetTransform().position.y << ", "
//				  << mainBody->GetTransform().position.z << '\n';
//
//		last = now;
//	}
}