#include "Knight.h"

Knight::Knight(int x, int y, const std::string spritename, const Board& brd)
	:
	Piece({ x,y }, spritename, brd)
{
}

void Knight::GetMoves(const Map* mypieces, const Map* opponentpieces, std::vector<Coords>& myTargetList, const Coords& enemyKingPos, std::vector<Coords>& EnemyTargetList)
{
	moves.clear();

	int new_x = 1;
	int new_y = 2;

	//check up
	if (mypieces->count({ coords.x - new_x,coords.y - new_y }) == 0 && (coords.y - new_y) >= minCoord.y 
		&& (coords.x - new_x) >= minCoord.x)
	{
		if (Coords{ coords.x - new_x,coords.y - new_y } != enemyKingPos)
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x - new_x,coords.y - new_y }));
		}
		myTargetList.push_back({ coords.x - new_x,coords.y - new_y });
	}

	if (mypieces->count({ coords.x + new_x,coords.y - new_y }) == 0 && (coords.y - new_y) >= minCoord.y
		&& (coords.x + new_x) <= maxCoord.x)
	{
		if (Coords{ coords.x + new_x,coords.y - new_y } != enemyKingPos)
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x + new_x,coords.y - new_y }));
		}
		myTargetList.push_back({ coords.x + new_x,coords.y - new_y });		
	}

	//check down
	if (mypieces->count({ coords.x - new_x,coords.y + new_y }) == 0 && (coords.y + new_y) <= maxCoord.y
		&& (coords.x - new_x) >= minCoord.x)
	{
		if (Coords{ coords.x - new_x,coords.y + new_y } != enemyKingPos)
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x - new_x,coords.y + new_y }));
		}
		myTargetList.push_back({ coords.x - new_x,coords.y + new_y });
	}

	if (mypieces->count({ coords.x + new_x,coords.y + new_y }) == 0 && (coords.y + new_y) <= maxCoord.y
		&& (coords.x + new_x) <= maxCoord.x)
	{
		if (Coords{ coords.x + new_x,coords.y + new_y } != enemyKingPos)
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x + new_x,coords.y + new_y }));
		}
		myTargetList.push_back({ coords.x + new_x,coords.y + new_y });
	}

	//check left
	new_x = 2;
	new_y = 1;

	if (mypieces->count({ coords.x - new_x,coords.y + new_y }) == 0 && (coords.y + new_y) <= maxCoord.y
		&& (coords.x - new_x) >= minCoord.x)
	{
		if (Coords{ coords.x - new_x,coords.y + new_y } != enemyKingPos)
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x - new_x,coords.y + new_y }));
		}
		myTargetList.push_back({ coords.x - new_x,coords.y + new_y });
	}

	if (mypieces->count({ coords.x - new_x,coords.y - new_y }) == 0 && (coords.y - new_y) >= minCoord.y
		&& (coords.x - new_x) >= minCoord.x)
	{
		if (Coords{ coords.x - new_x,coords.y - new_y } != enemyKingPos)
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x - new_x,coords.y - new_y }));
		}
		myTargetList.push_back({ coords.x - new_x,coords.y - new_y });
	}

	if (mypieces->count({ coords.x + new_x,coords.y + new_y }) == 0 && (coords.y + new_y) <= maxCoord.y
		&& (coords.x + new_x) <= maxCoord.x)
	{
		if (Coords{ coords.x + new_x,coords.y + new_y } != enemyKingPos)
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x + new_x,coords.y + new_y }));
		}
		myTargetList.push_back({ coords.x + new_x,coords.y + new_y });
	}

	if (mypieces->count({ coords.x + new_x,coords.y - new_y }) == 0 && (coords.y - new_y) >= minCoord.y
		&& (coords.x + new_x) <= maxCoord.x)
	{
		if (Coords{ coords.x + new_x,coords.y - new_y } != enemyKingPos)
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x + new_x,coords.y - new_y }));
		}
		myTargetList.push_back({ coords.x + new_x,coords.y - new_y });
	}
}
