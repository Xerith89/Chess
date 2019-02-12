#pragma once
#include "Piece.h"

class Knight : public Piece {
public:
	Knight(int x, int y, const std::string spritename);
	void GetMoves(Map* mypieces, Map* opponentpieces)override;
private:
};