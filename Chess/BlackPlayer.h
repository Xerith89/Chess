#pragma once
#include "Actor.h"
#include "Timer.h"

class BlackPlayer : public Actor{
public:
	BlackPlayer(Window& wnd, Board& brd, GUI& gui);
	void DoTurn() override;
	void Promote(Map* map)override;
	void TestForCheck() override;
	bool TestForDraw()override;
	int GetPromotedPiece()const;
	//Draw Funcs
	void DrawPieces(Graphics& gfx)const override;
	void DrawChecked(Graphics& gfx)const override;
	void DrawPossibleMoves(Graphics& gfx);
	//Multiplayer Funcs
	void mDoTurn();
	void mPromote(Map* map);
	void SetPlayerTurn(bool myTurn);
	void DoMPlayUpdate(const std::pair<Coords, Coords> input, const int promoteType);
	bool PacketReady()const;
	void SetPacketNotReady();
	bool PlayerTurn()const;
private:
	int promotedPiece;
	GUI& gui;
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
	void RandomMoves();
	void MinimaxMoves();
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
	std::pair<Coords, Coords> worstMove;
	std::vector<std::pair<Coords, Coords>> equalMoves;
	int value = 0;
	void UndoWhiteMove();
	void TestBlackMove(std::pair<Coords, Coords>);
	void UndoBlackMove();
	int TestMoveScore()const;
	void DoWhiteMove(const std::pair<Coords, Coords> input);
	std::pair<Coords, Coords> Minimax(std::vector<std::pair<Coords, Coords>> moves_in);
};