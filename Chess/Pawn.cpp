#include "Pawn.h"

Pawn::Pawn(int x, int y, const std::string spritename)
	:
	Piece({ x,y }, spritename)
{
}

