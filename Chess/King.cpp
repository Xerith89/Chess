#include "King.h"

King::King(int x, int y, const std::string spritename)
	:
	Piece({ x,y }, spritename)
{
}

void King::GetMoves(const Map* mypieces,const Map* opponentpieces)
{
	moves.clear();

	int new_x = 1;
	int new_y = 1;
	//Check pieces left up - we don't want to go past our white pieces or the end of the board
	if (mypieces->count({ coords.x - new_x,coords.y - new_y }) == 0 && (coords.x - new_x) >= minCoord.x
		&& (coords.y - new_y) >= minCoord.y)
	{
		moves.push_back({ coords.x - new_x,coords.y - new_y });		
	}

	
	//Check pieces right up - we don't want to go past our white pieces or the end of the board
	if (mypieces->count({ coords.x + new_x,coords.y - new_y }) == 0 && (coords.x + new_x) <= maxCoord.x
		&& (coords.y - new_y) >= minCoord.y)
	{
		moves.push_back({ coords.x + new_x,coords.y - new_y });
		
	}

	//Check pieces right down - we don't want to go past our white pieces or the end of the board
	if (mypieces->count({ coords.x + new_x,coords.y + new_y }) == 0 && (coords.x + new_x) <= maxCoord.x
		&& (coords.y + new_y) <= maxCoord.y)
	{
		moves.push_back({ coords.x + new_x,coords.y + new_y });
	}

	//Check pieces left down - we don't want to go past our white pieces or the end of the board
	if (mypieces->count({ coords.x - new_x,coords.y + new_y }) == 0 && (coords.x - new_x) >= minCoord.x
		&& (coords.y + new_y) <= maxCoord.y)
	{
		moves.push_back({ coords.x - new_x,coords.y + new_y });
	}

	if (mypieces->count({ coords.x - new_x,coords.y }) == 0 && (coords.x - new_x) >= minCoord.x)
	{
		moves.push_back({ coords.x - new_x,coords.y });
	}
	//check right
	if (mypieces->count({ coords.x + new_x,coords.y }) == 0 && (coords.x + new_x) <= maxCoord.x)
	{
		moves.push_back({ coords.x + new_x,coords.y });
	}

	//check up
	if (mypieces->count({ coords.x,coords.y - new_y }) == 0 && (coords.y - new_y) >= minCoord.y)
	{
		moves.push_back({ coords.x,coords.y - new_y });
	}
	
	//Check down
	if (mypieces->count({ coords.x,coords.y + new_y }) == 0 && (coords.y + new_y) <= maxCoord.y)
	{
		moves.push_back({ coords.x,coords.y + new_y });
	}
}
