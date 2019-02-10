#include "Pawn.h"

Pawn::Pawn(int x, int y, const std::string spritename)
	:
	Piece({ x,y }, spritename)
{
	moveRules.push_back({ 0,2 });
	moveRules.push_back({ 0,1 });
}

