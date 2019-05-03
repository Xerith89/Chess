#pragma once
#include <enet.h>
#include "Sprite.h"
#include "Graphics.h"
#include <array>

class Server {
private:
	std::array<Sprite, 2> hostStates = { "./Sprites/Multiplayer/hosting.bmp" , "./Sprites/Multiplayer/waiting.bmp" };
	Sprite cancel;
	int hostState = 0;
	enum ServerStatus {
		STARTING,
		WAITING,
		CONNECTED
	};
	int serverState = ServerStatus::STARTING;
	ENetAddress address;
	ENetHost* server;
	ENetEvent event;
	ENetPeer* client;
public:
	void WaitForConnections();
	void DrawStates(Graphics& gfx)const;
	void CreateServer();
	void Cleanup();
	ENetEvent ReceivePacket();
	void SendPacket(std::string data);
	int GetServerStatus()const;
	Server();
	~Server();
};