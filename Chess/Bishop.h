#pragma once
#include "Piece.h"

class Bishop : public Piece {
public:
	Bishop(int x, int y, const std::string spritename);
	void GetMoves(Map* white, Map* black)override;
private:
};