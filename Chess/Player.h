#pragma once
#include "Window.h"
#include "Board.h"
#include "Graphics.h"

class Player {
public:
	Player(Window& wnd, Board& brd);
	void DoTurn();
	void DrawPossibleMoves(Graphics& gfx);
	bool PlayerTurn();
	void SetPlayerTurn();
private:
	Sprite target;
	Window& wnd;
	Board& brd;
	Coords selectedPiece;
	Coords selectedTarget;
	bool pieceSelected = false;
	std::vector<Coords> selectedMoves;
	bool playerTurn = true;
};