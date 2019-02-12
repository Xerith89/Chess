#include "Rook.h"

Rook::Rook(int x, int y, const std::string spritename)
	:
	Piece({ x,y }, spritename)
{
}

void Rook::GetMoves(Map* mypieces, Map* opponentpieces)
{
	moves.clear();
	int new_x = 1;
	//Check pieces to our left - we don't want to go past our white pieces or the end of the board
	while (mypieces->count({ coords.x - new_x,coords.y }) == 0 && (coords.x - new_x) >= minCoord.x)
	{
		moves.push_back({ coords.x - new_x,coords.y});
		if (opponentpieces->count({ coords.x - new_x, coords.y }) > 0)
		{break;}
		new_x++;

	}
	//Reset x and check right
	new_x = 1;
	while (mypieces->count({ coords.x + new_x,coords.y }) == 0 && (coords.x + new_x) <= maxCoord.x)
	{
		moves.push_back({ coords.x + new_x,coords.y });
		if (opponentpieces->count({ coords.x + new_x, coords.y }) > 0)
		{break;}
		new_x++;
	
		
	}
	
	//check up
	int new_y = 1;
	while (mypieces->count({ coords.x,coords.y - new_y}) == 0 && (coords.y-new_y) >= minCoord.y)
	{
		moves.push_back({ coords.x,coords.y-new_y});
		if (opponentpieces->count({ coords.x,coords.y - new_y }) > 0)
		{break;}
		new_y++;
	}
	//Check down
	new_y = 1;
	while (mypieces->count({ coords.x,coords.y + new_y }) == 0 && (coords.y +new_y) <= maxCoord.y)
	{
		moves.push_back({ coords.x,coords.y + new_y });
		if (opponentpieces->count({ coords.x,coords.y + new_y }) > 0)
		{break;}
		new_y++;
	}
	
}
