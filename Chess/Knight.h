#pragma once
#include "Piece.h"

class Knight : public Piece {
public:
	Knight(int x, int y, const std::string spritename);
	void GetMoves(const Map* mypieces, const Map* opponentpieces)override;
private:
};