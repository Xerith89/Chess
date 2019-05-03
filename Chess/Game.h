#pragma once
#include "Server.h"
#include "Client.h"
#include "Graphics.h"
#include "Input.h"
#include "Sprite.h"
#include "Board.h"
#include "Pawn.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "BlackPlayer.h"
#include "WhitePlayer.h"
#include "GUI.h"
#include "Menu.h"

class Game {
private:
	Window& wnd;
	Graphics gfx;
	Sprite playerwin = ("./Sprites/checkmatepwin.bmp");
	Sprite playerlose = ("./Sprites/checkmateplose.bmp");
	Sprite stalemate = ("./Sprites/stalemate.bmp");
	void Render();
	void Update();
	//Controls the state of the overrall program
	enum ProgramState {
		MAINMENU,
		PLAYING,
		HOSTING,
		JOINING,
		QUIT
	};
	//Controls the state of the game being played
	enum GameState {
		NORMAL,
		PLAYERCHECKED,
		OPPONENTCHECKED,
		PLAYERCHECKMATED,
		OPPONENTCHECKMATED,
		STALEMATE,
		DRAW
	};
	//variables for controlling enums
	int gameStatus;
	int programStatus;
	//Turn controllers
	bool playerTurn = true;
	bool opponentTurn = false;
	//Multiplayer
	bool isServer = false;
	bool clientTurn = false;
	bool isClient = false;
	bool isMultiplayer = false;
	//Local objects
	Board brd;
	WhitePlayer whitePlayer;
	BlackPlayer blackPlayer;
	GUI gui;
	Menu menu;
	Server server;
	Client client;
public:
	Game(Window& wnd);
	~Game() = default;
	Game(Game&) = delete;
	Game& operator=(Game&) = delete;
	void Run();
};
