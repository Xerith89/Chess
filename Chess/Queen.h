#pragma once
#include "Piece.h"

class Queen : public Piece {
public:
	Queen(int x, int y, const std::string spritename);
	void GetMoves(Map* mypieces, Map* opponentpieces)override;
private:
};