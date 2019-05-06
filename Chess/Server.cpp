#include "Server.h"

void Server::WaitForConnections()
{
	while (enet_host_service(server, &event, 0) > 0)
	{
		if (event.type == ENET_EVENT_TYPE_CONNECT)
		{
			client = event.peer;
			serverState = ServerStatus::CONNECTED;
		}
	}
}

void Server::DrawStates(Graphics& gfx) const
{
	gfx.DrawSprite(200, 180, hostStates.at(hostState));
	gfx.DrawSprite(300, 500, cancel);
}

void Server::CreateServer()
{
	if (enet_initialize() != 0)
	{
		throw std::runtime_error("An error occurred while initializing ENet.");
	}

	/* Bind the server to the default localhost.     */
	/* A specific host address can be specified by   */
	/* enet_address_set_host (& address, "x.x.x.x"); */
	address.host = ENET_HOST_ANY;
	/* Bind the server to port 1234. */
	address.port = 1234;
	server = enet_host_create(&address /* the address to bind the server host to */,
		1      /* allow up to 1 clients and/or outgoing connections */,
		2      /* allow up to 2 channels to be used, 0 and 1 */,
		0      /* assume any amount of incoming bandwidth */,
		0      /* assume any amount of outgoing bandwidth */);
	if (server == NULL)
	{
		throw std::runtime_error("An error occurred while trying to create an ENet server host.");
	}
	else
	{
		serverState = ServerStatus::WAITING;
		hostState = 1;
	}
}

void Server::Cleanup()
{
	hostState = 0;
	serverState = ServerStatus::STARTING;
	enet_host_destroy(server);
	enet_deinitialize();
}

ENetEvent Server::ReceivePacket()
{
	while (enet_host_service(server, &event, 0) > 0)
	{
		if (event.type == ENET_EVENT_TYPE_RECEIVE)
		{
			//Convert back to string and get our the coords
			std::string s(event.packet->data, event.packet->data + event.packet->dataLength);
			auto from = std::make_pair((s.at(0) - '0'), s.at(1) - '0');
			auto to = std::make_pair((s.at(2) - '0'), s.at(3) - '0');
			//Do black move with these coords
		}
		else if (event.type == ENET_EVENT_TYPE_DISCONNECT)
		{
			event.peer->data = NULL;
		}
	}
	return event;
}

void Server::SendPacket(std::string data)
{
	ENetPacket* packet = enet_packet_create(data.c_str(),
		data.size(),
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(client, 0, packet);
}

int Server::GetServerStatus() const
{
	return serverState;
}

Server::Server()
	:
	cancel("./Sprites/Multiplayer/cancel.bmp")
{
}

Server::~Server()
{
	enet_host_destroy(server);
}
