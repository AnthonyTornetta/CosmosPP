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

#include "source/netty/Constants.h"

void SendPacket(ENetPeer* peer, const char* data)
{
	ENetPacket* packet = enet_packet_create(data, strlen(data)+1, ENET_PACKET_FLAG_RELIABLE);
	// Second arg is channel:
	enet_peer_send(peer, 0, packet);
}

int main()
{
	std::atomic_bool isRunning{true};
	
	std::thread console([&]()
	{
		std::string line;
		while (isRunning)
		{
			std::cout << "Type a command.\n> ";
			std::getline(std::cin, line);
			if (line == "exit")
			{
				isRunning = false;
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
					
					break;
				}
				case ENET_EVENT_TYPE_RECEIVE:
				{
					if(event.packet->dataLength > 0)
					{
						std::stringstream ss((char*)event.packet->data); // Use std::ios::binary if filestream
						std::string str = ss.str();
						std::cout << str << std::endl;
					}
					
					enet_packet_destroy(event.packet);
					
					SendPacket(event.peer, "Got your message!");
					
					break;
				}
				case ENET_EVENT_TYPE_DISCONNECT:
				{
					printf("%s disconnected\n", event.peer->data);
					event.peer->data = NULL;
				}
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