#pragma once
#include "Window.h"
#include "Board.h"
#include "Graphics.h"
#include "King.h"

class Player {
	using Map = std::map<std::pair<int, int>, std::shared_ptr<Piece>>;
public:
	Player(Window& wnd, Board& brd);
	void DoTurn();
	void DrawPossibleMoves(Graphics& gfx);
	void DrawPieces(Graphics& gfx)const;
	bool PlayerTurn()const;
	void SetPlayerTurn();
	bool GetCMated()const;
private:
	King* kingInstance = nullptr;
	bool checked = false;
	bool cMated = false;
	void TestForCheck();
	Sprite target;
	Sprite inCheck;
	Window& wnd;
	Board& brd;
	Coords selectedPiece;
	Coords selectedTarget;
	bool pieceSelected = false;
	std::vector<std::pair<Coords, Coords>> selectedMoves;
	std::vector<std::pair<Coords, Coords>> movelist;
	bool playerTurn = true;
};