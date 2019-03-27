#include "Bishop.h"

Bishop::Bishop(int x, int y, const std::string spritename)
	:
	Piece({ x,y }, spritename)
{
}

void Bishop::GetMoves(const Map* mypieces, const Map* opponentpieces)
{
}
