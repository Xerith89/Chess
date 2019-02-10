#include "Pawn.h"

Pawn::Pawn(int x, int y, const std::string spritename)
	:
	Piece({ x,y }, spritename)
{
	movesTemplate.push_back({ 0,2 });
	movesTemplate.push_back({ 0,1 });
}

void Pawn::GetMoves()
{
	moves.clear();
	if (coords != startCoords) 
	{ 
		firstMove = false; 
	}

	if (firstMove)
	{
		for (const auto& x : movesTemplate)
		{
			moves.push_back({ coords.x,coords.y - x.y });
		}
	}
	else
	{
		moves.push_back({ coords.x,coords.y - 1 });
	}
}

