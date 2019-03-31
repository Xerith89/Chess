#include "Rook.h"

Rook::Rook(int x, int y, const std::string spritename, const Board& brd)
	:
	Piece({ x,y }, spritename, brd)
{
}

void Rook::GetMoves(const Map* mypieces, const Map* opponentpieces, std::set<Coords>& myTargetList, const Coords& enemyKingPos, std::set<Coords>& EnemyTargetList)
{
	moves.clear();
	int new_x = 1;
	//Check pieces to our left - we don't want to go past our white pieces or the end of the board
	while (mypieces->count({ coords.x - new_x,coords.y }) == 0 && (coords.x - new_x) >= minCoord.x)
	{
		if (Coords{ coords.x - new_x,coords.y } != enemyKingPos)
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x - new_x,coords.y }));
		}
		myTargetList.insert(Coords{ coords.x - new_x,coords.y });
		
		if (opponentpieces->count({ coords.x - new_x, coords.y }) > 0)
		{break;}
		new_x++;

	}
	//Reset x and check right
	new_x = 1;
	while (mypieces->count({ coords.x + new_x,coords.y }) == 0 && (coords.x + new_x) <= maxCoord.x)
	{
		if (Coords{ coords.x + new_x,coords.y } != enemyKingPos)
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x + new_x,coords.y }));
		}
		myTargetList.insert(Coords{ coords.x + new_x,coords.y });
	
		if (opponentpieces->count({ coords.x + new_x, coords.y }) > 0)
		{break;}
		new_x++;
	
		
	}
	
	//check up
	int new_y = 1;
	while (mypieces->count({ coords.x,coords.y - new_y}) == 0 && (coords.y-new_y) >= minCoord.y)
	{
		if (Coords{ coords.x,coords.y - new_y } != enemyKingPos)
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x,coords.y - new_y }));
		}
		myTargetList.insert(Coords{ coords.x,coords.y - new_y });
		
		if (opponentpieces->count({ coords.x,coords.y - new_y }) > 0)
		{break;}
		new_y++;
	}
	//Check down
	new_y = 1;
	while (mypieces->count({ coords.x,coords.y + new_y }) == 0 && (coords.y +new_y) <= maxCoord.y)
	{
		if (Coords{ coords.x,coords.y + new_y } != enemyKingPos)
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x,coords.y + new_y }));
		}
		myTargetList.insert(Coords{ coords.x,coords.y + new_y });
		
		if (opponentpieces->count({ coords.x,coords.y + new_y }) > 0)
		{break;}
		new_y++;
	}
}

std::vector<Coords> Rook::GetCheckedMoves(const Map * mypieces, const Map * opponentpieces)
{
	return std::vector<Coords>();
}
