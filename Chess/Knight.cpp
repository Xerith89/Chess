#include "Knight.h"

Knight::Knight(int x, int y, const std::string spritename)
	:
	Piece({ x,y }, spritename)
{
}

void Knight::GetMoves(const Map* mypieces, const Map* opponentpieces)
{
	moves.clear();

	int new_x = 1;
	int new_y = 2;

	//check up
	if (mypieces->count({ coords.x - new_x,coords.y - new_y }) == 0 && (coords.y - new_y) >= minCoord.y 
		&& (coords.x - new_x) >= minCoord.x)
	{
		moves.push_back(std::make_pair(coords, Coords{ coords.x - new_x,coords.y - new_y }));
	}

	if (mypieces->count({ coords.x + new_x,coords.y - new_y }) == 0 && (coords.y - new_y) >= minCoord.y
		&& (coords.x + new_x) <= maxCoord.x)
	{
		moves.push_back(std::make_pair(coords, Coords{ coords.x + new_x,coords.y - new_y }));
	}

	//check down
	if (mypieces->count({ coords.x - new_x,coords.y + new_y }) == 0 && (coords.y + new_y) <= maxCoord.y
		&& (coords.x - new_x) >= minCoord.x)
	{
		moves.push_back(std::make_pair(coords, Coords{ coords.x - new_x,coords.y + new_y }));
	}

	if (mypieces->count({ coords.x + new_x,coords.y + new_y }) == 0 && (coords.y + new_y) <= maxCoord.y
		&& (coords.x + new_x) <= maxCoord.x)
	{
		moves.push_back(std::make_pair(coords, Coords{ coords.x + new_x,coords.y + new_y }));
	}

	//check left
	new_x = 2;
	new_y = 1;

	if (mypieces->count({ coords.x - new_x,coords.y + new_y }) == 0 && (coords.y + new_y) <= maxCoord.y
		&& (coords.x - new_x) >= minCoord.x)
	{
		moves.push_back(std::make_pair(coords, Coords{ coords.x - new_x,coords.y + new_y }));
	}

	if (mypieces->count({ coords.x - new_x,coords.y - new_y }) == 0 && (coords.y - new_y) >= minCoord.y
		&& (coords.x - new_x) >= minCoord.x)
	{
		moves.push_back(std::make_pair(coords, Coords{ coords.x - new_x,coords.y - new_y }));
	}

	if (mypieces->count({ coords.x + new_x,coords.y + new_y }) == 0 && (coords.y + new_y) <= maxCoord.y
		&& (coords.x + new_x) <= maxCoord.x)
	{
		moves.push_back(std::make_pair(coords, Coords{ coords.x + new_x,coords.y + new_y }));
	}

	if (mypieces->count({ coords.x + new_x,coords.y - new_y }) == 0 && (coords.y - new_y) >= minCoord.y
		&& (coords.x + new_x) <= maxCoord.x)
	{
		moves.push_back(std::make_pair(coords, Coords{ coords.x + new_x,coords.y - new_y }));
	}
}
