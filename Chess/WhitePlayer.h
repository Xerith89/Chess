#pragma once
#include "Actor.h"


class WhitePlayer : public Actor {
public:
	WhitePlayer(Window& wnd, Board& brd, GUI& gui);
	void DoTurn()override;
	//Drawing Funcs
	void DrawPossibleMoves(Graphics& gfx);
	void DrawPieces(Graphics& gfx)const override;
	void DrawChecked(Graphics& gfx)const override;
	void DrawBestMove(Graphics& gfx)const;
	//Multiplayer
	bool PacketReady()const;
	void SetPacketNotReady();
	void DoMPlayUpdate(const std::pair<Coords, Coords> input, const int promoteType);
	//Game State Tests
	void TestForCheck()override;
	bool TestForDraw()override;
	void Promote(Map* map)override;
	bool PlayerTurn()const;
	void SetPlayerTurn(bool myTurn);
	int GetPromotedPiece() const;
	void GetBestMove();
private:
	int promotedPiece;
	Sprite bestSprite;
	GUI& gui;
	Coords startKingLoc = { 4,7 };
	Coords leftRookStartLoc = { 0,7 };
	Coords rightRookStartLoc = { 7,7 };
	void TestForStaleMate()override;
	void TestForCastling()override;
	bool TestForCheckMate()override;
	Coords selectedPiece;
	Coords selectedTarget;
	std::vector<std::pair<Coords, Coords>> selectedMoves;
	bool playerTurn = true;
	bool pieceSelected = false;
	bool packetReady = false;
	bool showBest = false;
	//Minimax variables
	std::mt19937 rng;
	std::random_device rd;
	Map blackInitialState;
	Map whiteInitialState;
	std::set<Coords> initialWhitePieceTargets;
	std::set<Coords> initialBlackPieceTargets;
	Coords initialWhiteKingLoc = brd.GetWhiteKingLoc();
	Coords initialBlackKingLoc = brd.GetBlackKingLoc();
	std::pair<Coords, Coords> bestMove;
	std::vector<std::pair<Coords, Coords>> equalMoves;
	int value = 0;
	void UndoWhiteMove();
	void DoBlackMove(std::pair<Coords, Coords> input);
	void UndoBlackMove();
	int TestMoveScore()const;
	void DoWhiteMove(const std::pair<Coords, Coords> input);
	std::pair<Coords, Coords> MinimaxAB(std::vector<std::pair<Coords, Coords>> moves_in);
};