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
#include "irrKlang.h"
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_dx11.h"
#include "../imgui/imgui_impl_win32.h"
#include "imgui_manager.h"

#pragma comment(lib, "irrKlang.lib")

class Game {
private:
	Window& wnd;
	Graphics gfx;
	Sprite playerwin;
	Sprite playerlose;
	Sprite stalemate;
	Sprite draw;
	irrklang::ISoundEngine* engine;
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
	//Sounds
	bool staleSound = true;
	bool checkSound = true;
	bool checkmateSound = true;
	bool drawSound = true;
	bool pieceSound = true;
	//Local objects
	Board brd;
	WhitePlayer whitePlayer;
	BlackPlayer blackPlayer;
	GUI gui;
	Menu menu;
	Server server;
	std::string data;
	Client client;
public:
	Game(Window& wnd);
	~Game() = default;
	Game(Game&) = delete;
	Game& operator=(Game&) = delete;
	void Run();
};
