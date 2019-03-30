#pragma once
#include "Window.h"
#include "Board.h"
#include "Graphics.h"
#include "King.h"

class Player {
	using Map = std::map<std::pair<int, int>, std::unique_ptr<Piece>>;
public:
	Player(Window& wnd, Board& brd);
	void DoTurn();
	void DrawPossibleMoves(Graphics& gfx);
	bool PlayerTurn()const;
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