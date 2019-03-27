#pragma once
#include "Piece.h"

class Queen : public Piece {
public:
	Queen(int x, int y, const std::string spritename);
	void GetMoves(const Map* mypieces, const Map* opponentpieces)override;
private:
};