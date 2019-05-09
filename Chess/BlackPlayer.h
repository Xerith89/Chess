#pragma once
#include "Actor.h"
#include "Timer.h"

class BlackPlayer : public Actor{
public:
	BlackPlayer(Window& wnd, Board& brd);
	void DoTurn() override;
	void DrawPieces(Graphics& gfx)const override;
	void DrawChecked(Graphics& gfx)const override;
	void Promote(Map* map)override;
	void TestForCheck() override;
	void mDoTurn();
	bool PacketReady()const;
	void SetPacketNotReady();
	bool PlayerTurn()const;
	void SetPlayerTurn(bool myTurn);
	void DoMPlayUpdate(std::pair<Coords, Coords> input);
	void DrawPossibleMoves(Graphics& gfx);
	bool TestForDraw()override;
private:
	Coords selectedPiece;
	Coords selectedTarget;
	std::vector<std::pair<Coords, Coords>> selectedMoves;
	bool playerTurn = false;
	bool pieceSelected = false;
	bool packetReady = false;
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
	Sprite promotionSprite;
	std::random_device rd;
	std::mt19937 rng;
	Timer timer;
	//Minimax variables
	Map initialState;
	Map whiteInitialState;
	std::set<Coords> initialWhitePieceTargets;
	std::set<Coords> initialBlackPieceTargets;
	Coords initialWhiteKingLoc = brd.GetWhiteKingLoc();
	Coords initialBlackKingLoc = brd.GetBlackKingLoc();
	std::pair<Coords, Coords> bestMove;
	std::vector<std::pair<Coords, Coords>> equalMoves;
	void ResetWhiteMove();
	void TestMove(std::pair<Coords, Coords>);
	void UndoTestMove();
	int TestMoveScore()const;
	void DoWhiteMove(const std::pair<Coords, Coords> input);
	std::pair<Coords, Coords> Minimax(std::vector<std::pair<Coords, Coords>> moves_in);
};