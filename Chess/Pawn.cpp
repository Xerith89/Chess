#include "Pawn.h"

Pawn::Pawn(int x, int y, const std::string spritename, bool white)
	:
	Piece({ x,y }, spritename),
	whitePiece(white)
{
	startCoords = { x,y };
}

void Pawn::GetMoves(const Map* mypieces, const Map* opponentpieces)
{
	//Empty out the moves list from the previous piece
	moves.clear();
	
	//If we are a black piece we need to invert our variables for movement and attack to result in a positive when put into our checking functions
	if (!whitePiece)
	{
		y_offset = -1;
		attackOffset = -attackOffset;
	}

	//Pawns can move 2 places on the first go so check if we've moved yet
	if (coords != startCoords) 
	{ 
		firstMove = false; 
	}
	
	//If we haven't moved then we want to check if the place is free up to two times
	if (firstMove)
	{
		while (mypieces->count({ coords.x, coords.y - y_offset }) == 0 && std::abs(y_offset) < 3)
		{
			if (opponentpieces->count({ coords.x,coords.y - y_offset }) == 0)
			{
				
				assert(y_offset < 10);
				moves.push_back(std::make_pair(coords, Coords{ coords.x,coords.y - y_offset}));
				y_offset+=y_offset;
			}
			else
			{
				break;
			}
		}
	}
	else
	{
		//reset our move offset based on whether we are a white or black piece
		(whitePiece) ? y_offset = 1 : y_offset = -1;
	//If we have moved then just check the next 
		while (mypieces->count({ coords.x,coords.y - y_offset }) == 0 && y_offset < 2)
		{
			if (opponentpieces->count({ coords.x,coords.y - y_offset }) == 0)
			{
				assert(y_offset < 10);
				moves.push_back(std::make_pair(coords, Coords{ coords.x,coords.y - y_offset }));
			}
			y_offset++;
		}
	}
	
	//Check if we have any diagonal black pieces at our current space - they  can be taken and are a possible move
	if (opponentpieces->count({ coords.x - 1,coords.y - attackOffset }) == 1)
	{
		assert(y_offset < 10);
		moves.push_back(std::make_pair(coords, Coords{ coords.x - 1,coords.y - attackOffset }));
	}

	if (opponentpieces->count({ coords.x + 1,coords.y - attackOffset }) == 1)
	{
		assert(y_offset < 10);
		moves.push_back(std::make_pair(coords, Coords{ coords.x + 1,coords.y - attackOffset }));
	}		
}

