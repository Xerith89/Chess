#pragma once
#include "Actor.h"

class Opponent : public Actor{
public:
	Opponent(Window& wnd, Board& brd);
	void DoTurn() override;
	void DrawPieces(Graphics& gfx)const override;
	void DrawChecked(Graphics& gfx)const override;
	void TestForCheck() override;
private:
	void GenerationZero();
	bool humanOpponent;
	std::random_device rd;
	std::mt19937 rng;
};