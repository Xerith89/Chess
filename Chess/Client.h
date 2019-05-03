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
	ENetPeer* GetPeer()const;
	ENetEvent ReceivePacket();
	void SendPacket(std::string data);
	Client();
	~Client();
	int GetStatus()const;
private:
	std::array<Sprite, 3> joinStates = { "./Sprites/Multiplayer/searching.bmp" , "./Sprites/Multiplayer/nogames.bmp","./Sprites/Multiplayer/searching.bmp" };
	Sprite cancel;
	enum ClientStates {
		SEARCHING,
		NONE,
		CONNECTED
	};
	int joinState = 0;
	int clientStatus = 0;
	ENetHost* client = nullptr;
	ENetAddress address;
	ENetEvent event;
	ENetPeer* peer = nullptr;

};