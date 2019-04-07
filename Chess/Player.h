#pragma once
#include "Actor.h"
#include "GUI.h"

class Player : public Actor {
public:
	Player(Window& wnd, Board& brd, GUI& gui);
	void DoTurn()override;
	void DrawPossibleMoves(Graphics& gfx);
	void DrawPieces(Graphics& gfx)const override;
	void DrawChecked(Graphics& gfx)const override;
	void Promote(Map* map)override;
	bool PlayerTurn()const;
	void SetPlayerTurn();
private:
	GUI& gui;
	void TestPawnPromotion()override;
	void TestForStaleMate()override;
	void TestForCheck()override;
	bool TestForCheckMate()override;
	Coords selectedPiece;
	Coords selectedTarget;
	std::vector<std::pair<Coords, Coords>> selectedMoves;
	bool playerTurn = true;
	bool pieceSelected = false;
};