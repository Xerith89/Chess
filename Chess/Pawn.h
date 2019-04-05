#pragma once
#include "Piece.h"

class Pawn : public Piece {
public:
	Pawn(int x, int y, const std::string spritename, bool white, Board& brd);
	virtual std::vector<std::pair<Coords, Coords>> GetMoves()override;
	virtual void GetTargets(Map* oppoPieces)override;
private:
	//Pawns can go two spaces in their first move so this will be used to populate move list each selection
	bool firstMove = true;
	int attackOffset = 1;
	int y_offset = 1;
};