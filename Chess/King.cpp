#include "King.h"

King::King(int x, int y, const std::string spritename)
	:
	Piece({ x,y }, spritename)
{
}

void King::GetMoves(Map* mypieces, Map* opponentpieces)
{
}
