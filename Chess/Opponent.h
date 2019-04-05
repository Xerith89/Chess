#pragma once
#include "Actor.h"
#include "Timer.h"

class Opponent : public Actor{
public:
	Opponent(Window& wnd, Board& brd);
	void DoTurn() override;
	void DrawPieces(Graphics& gfx)const override;
	void DrawChecked(Graphics& gfx)const override;
	void DrawPromotion(Graphics& gfx)const override;
private:
	void TestForCheck() override;
	bool TestForCheckMate()override;
	void TestPawnPromotion()override;
	void TestForStaleMate() override;
	void GenerationZero();
	void GenerationOne();
	void GenerationTwo();
	void GenerationThree();
	void GenerationFour();
	void GenerationFive();
	void GenerationSix();
	bool humanOpponent;
	Sprite promotionSprite;
	std::random_device rd;
	std::mt19937 rng;
	Timer timer;
};