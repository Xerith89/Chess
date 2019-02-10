#include "Pawn.h"

Pawn::Pawn(int x, int y, const std::string spritename)
	:
	Piece({ x,y }, spritename)
{
	movesTemplate.push_back({ 0,2 });
	movesTemplate.push_back({ 0,1 });
}

