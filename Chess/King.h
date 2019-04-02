#pragma once
#include "Piece.h"

class King : public Piece {
public:
	King(int x, int y, const std::string spritename,bool white, Board& brd);
	virtual std::vector<std::pair<Coords, Coords>> GetMoves()override;
	virtual std::vector<std::pair<Coords, Coords>> GetCheckedMoves()override;
private:

};
