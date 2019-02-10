#include "Pawn.h"

Pawn::Pawn(int x, int y, const std::string spritename)
	:
	Piece({ x,y }, spritename)
{
	movesTemplate.push_back({ 0,2 });
	movesTemplate.push_back({ 0,1 });
}

void Pawn::GetMoves(Map* white, Map* black)
{
	//Empty out the moves list from the previous piece
	moves.clear();
	//Pawns can move 2 places on the first go so check if we've moved yet
	if (coords != startCoords) 
	{ 
		firstMove = false; 
	}
	int moveCount = 0;
	
	//If we haven't moved then we want to check if the place is free up to two times
	if (firstMove)
	{
		int new_x = 1;
		while (white->count({ coords.x,coords.y - new_x }) == 0 && new_x != 3)
		{
			if (black->count({ coords.x,coords.y - new_x }) == 0)
			{
				moves.push_back({ coords.x,coords.y - new_x });
				new_x++;
			}
		}
	}
	else
	{
		//If we have moved then just check the next 
		int new_x = 1;
		while (white->count({ coords.x,coords.y - new_x }) == 0 && new_x < 2)
		{
			if (black->count({ coords.x,coords.y - new_x }) == 0)
			{
				moves.push_back({ coords.x,coords.y - new_x });
			}
			new_x++;
		}
	}

	//Check if we have any diagonal black pieces at our current space - they  can be taken and are a possible move
	if (black->count({ coords.x - 1,coords.y - 1 }) == 1)
	{
		moves.push_back({ coords.x-1,coords.y - 1 });
	}

	if (black->count({ coords.x + 1,coords.y - 1 }) == 1)
	{
		moves.push_back({ coords.x + 1,coords.y - 1 });
	}
}

