#pragma once
#include "Piece.h"

class King : public Piece {
public:
	King(int x, int y, const std::string spritename);
	void GetMoves(const Map* mypieces, const Map* opponentpieces)override;
private:

};
