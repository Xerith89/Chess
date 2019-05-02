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
	int serverStatus = 0;
	ENetAddress address;
	ENetHost* server;
public:
	void DrawStates(Graphics& gfx)const;
	void CreateServer();
	int GetServerStatus()const;
	Server();
	~Server();
};