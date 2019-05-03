#pragma once
#include <enet.h>
#include "Sprite.h"
#include "Graphics.h"
#include <array>

class Client {
public:
	void DrawStates(Graphics& gfx)const;
	void JoinGame();
	void SetState();
	Client();
	~Client();
	int GetStatus()const;
private:
	std::array<Sprite, 2> joinStates = { "./Sprites/Multiplayer/searching.bmp" , "./Sprites/Multiplayer/nogames.bmp" };
	Sprite cancel;
	enum ClientStates {
		SEARCHING,
		NONE,
		CONNECTED
	};
	int joinState = 0;
	int clientStatus = 0;
	ENetHost* client;
	ENetAddress address;
	ENetEvent event;
	ENetPeer* peer;

};