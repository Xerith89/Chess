#pragma once
#include "Piece.h"

class Rook : public Piece {
public:
	Rook(int x, int y, const std::string spritename);
	void GetMoves(const Map* mypieces, const Map* opponentpieces)override;
private:
};