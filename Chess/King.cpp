#include "King.h"
#include "Board.h"

King::King(int x, int y, const std::string spritename, const Board& brd)
	:
	Piece({ x,y }, spritename, brd)
{
}

std::vector<std::pair<Coords, Coords>> King::GetMoves(const Map* mypieces,const Map* opponentpieces, std::set<Coords>& myTargetList,const Coords& enemyKingPos, std::set<Coords>& EnemyTargetList)
{
	std::vector<std::pair<Coords, Coords>> moves;

	int new_x = 1;
	int new_y = 1;
	//Check pieces left up - we don't want to go past our white pieces or the end of the board
	if (mypieces->count({ coords.x - new_x,coords.y - new_y }) == 0 && (coords.x - new_x) >= minCoord.x
		&& (coords.y - new_y) >= minCoord.y && Coords{ coords.x - new_x,coords.y - new_y } != enemyKingPos)
	{
		if (std::none_of(EnemyTargetList.begin(), EnemyTargetList.end(), [&](const Coords rhs) {
			return rhs == Coords{ coords.x - new_x,coords.y - new_y }; }))
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x - new_x,coords.y - new_y }));
			myTargetList.insert(Coords{ coords.x - new_x,coords.y - new_y });
		}
	}

	
	//Check pieces right up - we don't want to go past our white pieces or the end of the board
	if (mypieces->count({ coords.x + new_x,coords.y - new_y }) == 0 && (coords.x + new_x) <= maxCoord.x
		&& (coords.y - new_y) >= minCoord.y && Coords{ coords.x + new_x,coords.y - new_y } != enemyKingPos)
	{
		if (std::none_of(EnemyTargetList.begin(), EnemyTargetList.end(), [&](const Coords rhs) {
			return rhs == Coords{ coords.x + new_x,coords.y - new_y }; }))
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x + new_x,coords.y - new_y }));
			myTargetList.insert(Coords{ coords.x + new_x,coords.y - new_y });
		}
	}

	//Check pieces right down - we don't want to go past our white pieces or the end of the board
	if (mypieces->count({ coords.x + new_x,coords.y + new_y }) == 0 && (coords.x + new_x) <= maxCoord.x
		&& (coords.y + new_y) <= maxCoord.y && Coords{ coords.x + new_x,coords.y + new_y } != enemyKingPos)
	{
		if (std::none_of(EnemyTargetList.begin(), EnemyTargetList.end(), [&](const Coords rhs) {
		return rhs == Coords{ coords.x + new_x,coords.y + new_y }; }))
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x + new_x,coords.y + new_y }));
			myTargetList.insert(Coords{ coords.x + new_x,coords.y + new_y });
		}
		
	}

	//Check pieces left down - we don't want to go past our white pieces or the end of the board
	if (mypieces->count({ coords.x - new_x,coords.y + new_y }) == 0 && (coords.x - new_x) >= minCoord.x
		&& (coords.y + new_y) <= maxCoord.y && Coords{ coords.x - new_x,coords.y + new_y } != enemyKingPos)
	{
		if (std::none_of(EnemyTargetList.begin(), EnemyTargetList.end(), [&](const Coords rhs) {
			return rhs == Coords{ coords.x - new_x,coords.y + new_y }; }))
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x - new_x,coords.y + new_y }));
			myTargetList.insert(Coords{ coords.x - new_x,coords.y + new_y });
		}
	}

	//check left
	if (mypieces->count({ coords.x - new_x,coords.y }) == 0 && (coords.x - new_x) >= minCoord.x && Coords{ coords.x - new_x,coords.y } != enemyKingPos)
	{
		if (std::none_of(EnemyTargetList.begin(), EnemyTargetList.end(), [&](const Coords rhs) {
			return rhs == Coords{ coords.x - new_x,coords.y }; }))
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x - new_x,coords.y }));
			myTargetList.insert(Coords{ coords.x - new_x,coords.y });
		}
	}
	//check right
	if (mypieces->count({ coords.x + new_x,coords.y }) == 0 && (coords.x + new_x) <= maxCoord.x && Coords{ coords.x + new_x,coords.y } != enemyKingPos)
	{
		if (std::none_of(EnemyTargetList.begin(), EnemyTargetList.end(), [&](const Coords rhs) {
		return rhs == Coords{ coords.x + new_x,coords.y }; }))
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x + new_x,coords.y }));
			myTargetList.insert(Coords{ coords.x + new_x,coords.y });
		}
		
	}

	//check up
	if (mypieces->count({ coords.x,coords.y - new_y }) == 0 && (coords.y - new_y) >= minCoord.y && Coords{ coords.x,coords.y - new_y } != enemyKingPos)
	{
		
		if (std::none_of(EnemyTargetList.begin(), EnemyTargetList.end(), [&](const Coords rhs) {
			return rhs == Coords{coords.x, coords.y - new_y }; }))
			{
				moves.push_back(std::make_pair(coords, Coords{ coords.x,coords.y - new_y }));
				myTargetList.insert(Coords{ coords.x,coords.y - new_y });
			}
		
	}
	
	//Check down
	if (mypieces->count({ coords.x,coords.y + new_y }) == 0 && (coords.y + new_y) <= maxCoord.y && Coords{ coords.x,coords.y + new_y} != enemyKingPos)
	{
		if (std::none_of(EnemyTargetList.begin(), EnemyTargetList.end(), [&](const Coords rhs) {
			return rhs == Coords{coords.x, coords.y + new_y}; }))
		{
				moves.push_back(std::make_pair(coords, Coords{ coords.x,coords.y + new_y }));
				myTargetList.insert(Coords{ coords.x,coords.y + new_y });
		}
	}
	return moves;
}

std::vector<Coords> King::GetCheckedMoves(const Map * mypieces, const Map * opponentpieces)
{
	return std::vector<Coords>();
}
