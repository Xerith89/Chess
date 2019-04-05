#pragma once
#include "Actor.h"

class Player : public Actor {
public:
	Player(Window& wnd, Board& brd);
	void DoTurn()override;
	void DrawPossibleMoves(Graphics& gfx);
	void DrawPieces(Graphics& gfx)const override;
	void DrawChecked(Graphics& gfx)const override;
	void DrawPromotion(Graphics& gfx)const override;
	bool PlayerTurn()const;
	void SetPlayerTurn();
private:
	void TestPawnPromotion()override;
	void TestForStaleMate()override;
	void TestForCheck()override;
	bool TestForCheckMate()override;
	Coords selectedPiece;
	Coords selectedTarget;
	Sprite promotionSprite;
	std::vector<std::pair<Coords, Coords>> selectedMoves;
	bool playerTurn = true;
	bool pieceSelected = false;
};