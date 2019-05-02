#include "Server.h"

void Server::DrawStates(Graphics& gfx) const
{
	gfx.DrawSprite(200, 180, hostStates.at(hostState));
	gfx.DrawSprite(300, 420, cancel);
}

void Server::CreateServer()
{
	if (enet_initialize() != 0)
	{
		fprintf(stderr, "An error occurred while initializing ENet.\n");
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
		fprintf(stderr,
			"An error occurred while trying to create an ENet server host.\n");
	}
	else
	{
		serverStatus = 1;
		hostState = 1;
	}
}

int Server::GetServerStatus() const
{
	return serverStatus;
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
