#pragma once
#include "Piece.h"

class King : public Piece {
public:
	King(int x, int y, const std::string spritename);
	void GetMoves(Map* white, Map* black)override;
private:

};
