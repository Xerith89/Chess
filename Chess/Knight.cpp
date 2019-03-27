#include "Knight.h"

Knight::Knight(int x, int y, const std::string spritename)
	:
	Piece({ x,y }, spritename)
{
}

void Knight::GetMoves(const Map* mypieces, const Map* opponentpieces)
{
}
