#pragma once
#include <enet.h>
#include "Sprite.h"
#include "Graphics.h"
#include <array>
#include "Coords.h"

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
	std::pair<Coords, Coords> GetLatestMove()const;
	bool CheckNewMessage()const;
	void SetNewMessage(bool status);
private:
	std::array<Sprite, 3> joinStates = { Sprite("./Sprites/Multiplayer/searching.bmp") , Sprite("./Sprites/Multiplayer/nogames.bmp"),Sprite("./Sprites/Multiplayer/searching.bmp") };
	Sprite cancel;
	enum ClientStates {
		SEARCHING,
		NONE,
		CONNECTED,
		DISCONNECTED
	};
	int joinState = 0;
	int clientStatus = 0;
	ENetHost* client = nullptr;
	ENetAddress address;
	ENetEvent event;
	ENetPeer* peer = nullptr;
	std::pair<int, int> to;
	std::pair<int, int> from;
	bool newMessage = false;
};