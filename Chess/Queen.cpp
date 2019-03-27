#include "Queen.h"

Queen::Queen(int x, int y, const std::string spritename)
	:
	Piece({ x,y }, spritename)
{
}

void Queen::GetMoves(const Map* mypieces, const Map* opponentpieces)
{
}
