#include "Bishop.h"
#include "Board.h"
Bishop::Bishop(int x, int y, const std::string spritename, const Board& brd)
	:
	Piece({ x,y }, spritename, brd)
{
}

std::vector<std::pair<Coords, Coords>> Bishop::GetMoves(const Map* mypieces, const Map* opponentpieces, std::set<Coords>& myTargetList,const Coords& enemyKingPos, std::set<Coords>& EnemyTargetList, const Coords & myKingPos)
{
	std::vector<std::pair<Coords, Coords>> moves;

	int new_x = 1;
	int new_y = 1;
	//Check pieces left up - we don't want to go past our white pieces or the end of the board
	while (mypieces->count({ coords.x - new_x,coords.y - new_y }) == 0 && (coords.x - new_x) >= minCoord.x 
		&& (coords.y - new_y) >= minCoord.y)
	{
		if (Coords{ coords.x - new_x, coords.y - new_y } != enemyKingPos)
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x - new_x,coords.y - new_y }));
		}
		myTargetList.insert(Coords{ coords.x - new_x,coords.y - new_y });
		
		if (opponentpieces->count({ coords.x - new_x, coords.y- new_y }) > 0)
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
		if (Coords{ coords.x + new_x,coords.y - new_y } != enemyKingPos)
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x + new_x,coords.y - new_y }));
		}
		myTargetList.insert(Coords{ coords.x + new_x,coords.y - new_y });

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
		if (Coords{ coords.x + new_x,coords.y + new_y } != enemyKingPos)
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x + new_x,coords.y + new_y }));
		}
		myTargetList.insert(Coords{ coords.x + new_x,coords.y + new_y } );
		
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
		if (Coords{ coords.x - new_x,coords.y + new_y } != enemyKingPos)
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x - new_x,coords.y + new_y }));
		}
		myTargetList.insert(Coords{ coords.x - new_x,coords.y + new_y });
		if (opponentpieces->count({ coords.x - new_x, coords.y + new_y }) > 0)
		{
			break;
		}
		new_x++;
		new_y++;
	}
	return moves;
}

std::vector<std::pair<Coords, Coords>> Bishop::GetCheckedMoves(const Map * mypieces, const Map * opponentpieces, std::set<Coords>& myTargetList, const Coords & enemyKingPos, std::set<Coords>& EnemyTargetList, const Coords & myKingPos)
{
	//Get every available move;
	auto allMoves = GetMoves(mypieces, opponentpieces, myTargetList, enemyKingPos, EnemyTargetList,  myKingPos);
	std::vector<std::pair<Coords, Coords>> trimMoves;
	//Go through the enemy target list and if it matches our move list then add it to the filtered move list
	for (const auto& m : EnemyTargetList)
	{
		auto it = (std::find_if(allMoves.begin(), allMoves.end(), [&](const std::pair<Coords, Coords>& rhs) {
			return m == rhs.second; }));

		if (it != allMoves.end())
		{
			trimMoves.push_back(*it);
		}
	}
	return trimMoves;
}


