#pragma once
#include "Actor.h"
#include "Timer.h"

class Opponent : public Actor{
public:
	Opponent(Window& wnd, Board& brd);
	void DoTurn() override;
	void DrawPieces(Graphics& gfx)const override;
	void DrawChecked(Graphics& gfx)const override;
	void Promote(Map* map)override;
	void TestForCheck() override;
private:
	Coords startKingLoc = { 4,0 };
	Coords leftRookStartLoc = { 0,0 };
	Coords rightRookStartLoc = { 7,0 };
	bool TestForCheckMate()override;
	void TestForStaleMate() override;
	void TestForCastling()override;
	void GenerationZero();
	void GenerationOne();
	void GenerationTwo();
	void GenerationThree();
	void GenerationFour();
	void GenerationFive();
	void GenerationSix();
	bool humanOpponent;
	std::pair<Coords,Coords> Minimax(int depth, bool isMaximising);
	Sprite promotionSprite;
	std::random_device rd;
	std::mt19937 rng;
	Timer timer;
	//Minimax variables
	Map initialState;
	Map whiteInitialState;
	std::pair<Coords, Coords> bestMove;
	int bestMoveValue;
};