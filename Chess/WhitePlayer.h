#pragma once
#include "Actor.h"
#include "GUI.h"

class WhitePlayer : public Actor {
public:
	WhitePlayer(Window& wnd, Board& brd, GUI& gui);
	void DoTurn()override;
	void DoMPlayUpdate(std::pair<Coords, Coords> input);
	void DrawPossibleMoves(Graphics& gfx);
	void DrawPieces(Graphics& gfx)const override;
	void DrawChecked(Graphics& gfx)const override;
	void Promote(Map* map)override;
	bool PlayerTurn()const;
	void SetPlayerTurn(bool myTurn);
	void TestForCheck()override;
	bool PacketReady()const;
	void SetPacketNotReady();
private:
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
	bool serverTurn = true;
	bool pieceSelected = false;
	bool packetReady = false;
};