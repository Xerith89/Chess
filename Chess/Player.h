#pragma once
#include "Window.h"
#include "Board.h"
#include "Graphics.h"
#include "King.h"

class Player {
public:
	Player(Window& wnd, Board& brd);
	void DoTurn();
	void DrawPossibleMoves(Graphics& gfx);
	bool PlayerTurn()const;
	void SetPlayerTurn();
	Coords GetKingPosition()const;
private:
	King* kingInstance = nullptr;
	Coords kingLoc = { 4, 7 };
	Sprite target;
	Window& wnd;
	Board& brd;
	Coords selectedPiece;
	Coords selectedTarget;
	bool pieceSelected = false;
	std::vector<Coords> selectedMoves;
	bool playerTurn = true;
};