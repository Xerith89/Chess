#pragma once
#include <enet.h>
#include "Sprite.h"
#include "Graphics.h"
#include <array>
#include "Coords.h"

class Server {
private:
	std::array<Sprite, 2> hostStates = { Sprite("./Sprites/Multiplayer/hosting.bmp") , Sprite("./Sprites/Multiplayer/waiting.bmp") };
	Sprite cancel;
	int hostState = 0;
	enum ServerStatus {
		STARTING,
		WAITING,
		CONNECTED,
		DISCONNECTED
	};
	int serverState = ServerStatus::STARTING;
	ENetAddress address;
	ENetHost* server;
	ENetEvent event;
	ENetPeer* client;
	std::pair<int, int> to;
	std::pair<int, int> from;
	bool newMessage = false;
public:
	bool CheckNewMessage()const;
	void SetNewMessage(bool status);
	void WaitForConnections();
	void DrawStates(Graphics& gfx)const;
	void CreateServer();
	void Cleanup();
	ENetEvent ReceivePacket();
	void SendPacket(std::string data);
	int GetServerStatus()const;
	std::pair<Coords, Coords> GetLatestMove()const;
	Server();
	~Server();
};