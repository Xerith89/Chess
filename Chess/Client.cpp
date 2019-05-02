#include "Client.h"

void Client::DrawStates(Graphics& gfx) const
{
	gfx.DrawSprite(200, 180, joinStates.at(clientStatus));
	gfx.DrawSprite(300, 500, cancel);
}

void Client::JoinGame()
{
	client = enet_host_create(NULL /* create a client host */,
		1 /* only allow 1 outgoing connection */,
		2 /* allow up 2 channels to be used, 0 and 1 */,
		0 /* assume any amount of incoming bandwidth */,
		0 /* assume any amount of outgoing bandwidth */);
	if (client == NULL)
	{
		fprintf(stderr,
			"An error occurred while trying to create an ENet client host.\n");
	}
	/* Connect to some.server.net:1234. */
	enet_address_set_host(&address, "127.0.0.1");
	address.port = 1234;
	/* Initiate the connection, allocating the two channels 0 and 1. */
	peer = enet_host_connect(client, &address, 1, 0);
	if (peer == NULL)
	{
		joinState = ClientStates::NONE;
	}
	/* Wait up to 5 seconds for the connection attempt to succeed. */
	if (enet_host_service(client, &event, 5000) > 0 &&
		event.type == ENET_EVENT_TYPE_CONNECT)
	{
		joinState = ClientStates::CONNECTED;
	}
	else {
		joinState = ClientStates::NONE;
		enet_peer_reset(peer);
		puts("Connection to some.server.net:1234 failed.");
	}

}

Client::Client()
	:
	cancel("./Sprites/Multiplayer/cancel.bmp")
{
}

Client::~Client()
{
	enet_host_destroy(client);
}

int Client::GetStatus() const
{
	return clientStatus;
}
