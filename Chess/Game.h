#pragma once
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
#include "Player.h"
#include "Opponent.h"
#include "GUI.h"

class Game {
private:
	Window& wnd;
	Graphics gfx;
	Sprite playerwin = ("./Sprites/checkmatepwin.bmp");
	Sprite playerlose = ("./Sprites/checkmateplose.bmp");
	Sprite stalemate = ("./Sprites/stalemate.bmp");
	void Render();
	void Update();
	enum GameState {
		NORMAL,
		PLAYERCHECKED,
		OPPONENTCHECKED,
		PLAYERCHECKMATED,
		OPPONENTCHECKMATED,
		STALEMATE
	};
	int gameStatus;
	bool playerTurn = true;
	bool opponentTurn = false;
public:
	Game(Window& wnd);
	~Game() = default;
	Game(Game&) = delete;
	Game& operator=(Game&) = delete;
	Board brd;
	Player player;
	Opponent opponent;
	GUI gui;
	void Run();
};
