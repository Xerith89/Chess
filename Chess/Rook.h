#pragma once
#include "Piece.h"

class Rook : public Piece {
public:
	Rook(int x, int y, const std::string spritename);
	void GetMoves(Map* white, Map* black)override;
private:
};