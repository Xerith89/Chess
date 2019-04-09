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
	void TestMove(std::pair<Coords, Coords>);
	void UndoTestMove();
	int TestMoveScore()const;
	bool humanOpponent;
	std::pair<Coords,Coords> Minimax(int depth, bool isMaximising, std::vector<std::pair<Coords,Coords>> moves_in);
	Sprite promotionSprite;
	std::random_device rd;
	std::mt19937 rng;
	Timer timer;
	//Minimax variables
	int value = 0;
	Map initialState;
	Map whiteInitialState;
	std::set<Coords> initialWhitePieceTargets;
	std::set<Coords> initialBlackPieceTargets;
	Coords initialWhiteKingLoc;
	Coords initialBlackKingLoc;
	std::pair<Coords, Coords> bestMove;
	int bestMoveValueNeg = -99999;
	int bestMoveValue = 99999;
	Map TestPieceMoves;
	std::set<Coords> TestPieceTargets;
	std::vector<std::pair<Coords, Coords>> equalMoves;
	std::vector<std::pair<Coords, Coords>> nextDepth;
	Map OpponentPieceMap;
};