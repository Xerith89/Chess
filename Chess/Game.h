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

class Game {
private:
	Window& wnd;
	Graphics gfx;
	void Render();
	void Update();
	enum GameState
	{
		MainMenu,
		LocalGame,
		MultiplayerGame,
		MultiplayerFind
	};
public:
	Game(Window& wnd);
	~Game() = default;
	Game(Game&) = delete;
	Game& operator=(Game&) = delete;
	Board brd;
	Player player;
	void Run();
};
