#pragma once
#include "Actor.h"

class Player : public Actor {
public:
	Player(Window& wnd, Board& brd);
	void DoTurn()override;
	void DrawPossibleMoves(Graphics& gfx);
	void DrawPieces(Graphics& gfx)const override;
	void DrawChecked(Graphics& gfx)const override;
	bool PlayerTurn()const;
	void SetPlayerTurn();
	void TestForCheck()override;
private:
	Coords selectedPiece;
	Coords selectedTarget;
	bool pieceSelected = false;
	std::vector<std::pair<Coords, Coords>> selectedMoves;
	bool playerTurn = true;
};