#include "Queen.h"

Queen::Queen(int x, int y, const std::string spritename)
	:
	Piece({ x,y }, spritename)
{
}

void Queen::GetMoves(const Map* mypieces, const Map* opponentpieces)
{

	moves.clear();

	int new_x = 1;
	int new_y = 1;
	//Check pieces left up - we don't want to go past our white pieces or the end of the board
	while (mypieces->count({ coords.x - new_x,coords.y - new_y }) == 0 && (coords.x - new_x) >= minCoord.x
		&& (coords.y - new_y) >= minCoord.y)
	{
		moves.push_back({ coords.x - new_x,coords.y - new_y });
		if (opponentpieces->count({ coords.x - new_x, coords.y - new_y }) > 0)
		{
			break;
		}
		new_x++;
		new_y++;
	}

	new_x = 1;
	new_y = 1;
	//Check pieces right up - we don't want to go past our white pieces or the end of the board
	while (mypieces->count({ coords.x + new_x,coords.y - new_y }) == 0 && (coords.x + new_x) <= maxCoord.x
		&& (coords.y - new_y) >= minCoord.y)
	{
		moves.push_back({ coords.x + new_x,coords.y - new_y });
		if (opponentpieces->count({ coords.x + new_x, coords.y - new_y }) > 0)
		{
			break;
		}
		new_x++;
		new_y++;
	}

	new_x = 1;
	new_y = 1;
	//Check pieces right down - we don't want to go past our white pieces or the end of the board
	while (mypieces->count({ coords.x + new_x,coords.y + new_y }) == 0 && (coords.x + new_x) <= maxCoord.x
		&& (coords.y + new_y) <= maxCoord.y)
	{
		moves.push_back({ coords.x + new_x,coords.y + new_y });
		if (opponentpieces->count({ coords.x + new_x, coords.y + new_y }) > 0)
		{
			break;
		}
		new_x++;
		new_y++;
	}

	new_x = 1;
	new_y = 1;
	//Check pieces left down - we don't want to go past our white pieces or the end of the board
	while (mypieces->count({ coords.x - new_x,coords.y + new_y }) == 0 && (coords.x - new_x) >= minCoord.x
		&& (coords.y + new_y) <= maxCoord.y)
	{
		moves.push_back({ coords.x - new_x,coords.y + new_y });
		if (opponentpieces->count({ coords.x - new_x, coords.y + new_y }) > 0)
		{
			break;
		}
		new_x++;
		new_y++;
	}

	while (mypieces->count({ coords.x - new_x,coords.y }) == 0 && (coords.x - new_x) >= minCoord.x)
	{
		moves.push_back({ coords.x - new_x,coords.y });
		if (opponentpieces->count({ coords.x - new_x, coords.y }) > 0)
		{
			break;
		}
		new_x++;

	}
	//Reset x and check right
	new_x = 1;
	while (mypieces->count({ coords.x + new_x,coords.y }) == 0 && (coords.x + new_x) <= maxCoord.x)
	{
		moves.push_back({ coords.x + new_x,coords.y });
		if (opponentpieces->count({ coords.x + new_x, coords.y }) > 0)
		{
			break;
		}
		new_x++;
	}
	
	new_x = 1;
	while (mypieces->count({ coords.x - new_x,coords.y }) == 0 && (coords.x - new_x) >= minCoord.x)
	{
		moves.push_back({ coords.x - new_x,coords.y });
		if (opponentpieces->count({ coords.x - new_x, coords.y }) > 0)
		{
			break;
		}
		new_x++;
	}
	new_y = 1;
	//check up
	while (mypieces->count({ coords.x,coords.y - new_y }) == 0 && (coords.y - new_y) >= minCoord.y)
	{
		moves.push_back({ coords.x,coords.y - new_y });
		if (opponentpieces->count({ coords.x,coords.y - new_y }) > 0)
		{
			break;
		}
		new_y++;
	}
	//Check down
	new_y = 1;
	while (mypieces->count({ coords.x,coords.y + new_y }) == 0 && (coords.y + new_y) <= maxCoord.y)
	{
		moves.push_back({ coords.x,coords.y + new_y });
		if (opponentpieces->count({ coords.x,coords.y + new_y }) > 0)
		{
			break;
		}
		new_y++;
	}
}
