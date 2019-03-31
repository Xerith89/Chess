#include "King.h"
#include "Board.h"

King::King(int x, int y, const std::string spritename, const Board& brd)
	:
	Piece({ x,y }, spritename, brd)
{
}

void King::GetMoves(const Map* mypieces,const Map* opponentpieces, std::vector<Coords>& myTargetList,const Coords& enemyKingPos, std::vector<Coords>& EnemyTargetList)
{
	moves.clear();

	int new_x = 1;
	int new_y = 1;
	//Check pieces left up - we don't want to go past our white pieces or the end of the board
	if (mypieces->count({ coords.x - new_x,coords.y - new_y }) == 0 && (coords.x - new_x) >= minCoord.x
		&& (coords.y - new_y) >= minCoord.y)
	{
		if (std::any_of(EnemyTargetList.begin(), EnemyTargetList.end(), [&](const Coords rhs) {
			return rhs != Coords{ coords.x - new_x,coords.y - new_y }; }))
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x - new_x,coords.y - new_y }));
			myTargetList.push_back({ coords.x - new_x,coords.y - new_y });
		}	
	}

	
	//Check pieces right up - we don't want to go past our white pieces or the end of the board
	if (mypieces->count({ coords.x + new_x,coords.y - new_y }) == 0 && (coords.x + new_x) <= maxCoord.x
		&& (coords.y - new_y) >= minCoord.y)
	{
		if (std::any_of(EnemyTargetList.begin(), EnemyTargetList.end(), [&](const Coords rhs) {
			return rhs != Coords{ coords.x + new_x,coords.y - new_y }; }))
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x + new_x,coords.y - new_y }));
			myTargetList.push_back({ coords.x + new_x,coords.y - new_y });
		}
	}

	//Check pieces right down - we don't want to go past our white pieces or the end of the board
	if (mypieces->count({ coords.x + new_x,coords.y + new_y }) == 0 && (coords.x + new_x) <= maxCoord.x
		&& (coords.y + new_y) <= maxCoord.y)
	{
		if (std::any_of(EnemyTargetList.begin(), EnemyTargetList.end(), [&](const Coords rhs) {
		return rhs != Coords{ coords.x + new_x,coords.y + new_y }; }))
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x + new_x,coords.y + new_y }));
			myTargetList.push_back({ coords.x + new_x,coords.y + new_y });
		}
		
	}

	//Check pieces left down - we don't want to go past our white pieces or the end of the board
	if (mypieces->count({ coords.x - new_x,coords.y + new_y }) == 0 && (coords.x - new_x) >= minCoord.x
		&& (coords.y + new_y) <= maxCoord.y)
	{
		if (std::any_of(EnemyTargetList.begin(), EnemyTargetList.end(), [&](const Coords rhs) {
			return rhs != Coords{ coords.x - new_x,coords.y + new_y }; }))
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x - new_x,coords.y + new_y }));
			myTargetList.push_back({ coords.x - new_x,coords.y + new_y });
		}
	}

	if (mypieces->count({ coords.x - new_x,coords.y }) == 0 && (coords.x - new_x) >= minCoord.x)
	{
		if (std::any_of(EnemyTargetList.begin(), EnemyTargetList.end(), [&](const Coords rhs) {
			return rhs != Coords{ coords.x - new_x,coords.y }; }))
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x - new_x,coords.y }));
			myTargetList.push_back({ coords.x - new_x,coords.y });
		}
	}
	//check right
	if (mypieces->count({ coords.x + new_x,coords.y }) == 0 && (coords.x + new_x) <= maxCoord.x)
	{
		if (std::any_of(EnemyTargetList.begin(), EnemyTargetList.end(), [&](const Coords rhs) {
		return rhs != Coords{ coords.x + new_x,coords.y }; }))
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x + new_x,coords.y }));
			myTargetList.push_back({ coords.x + new_x,coords.y });
		}
		
	}

	//check up
	if (mypieces->count({ coords.x,coords.y - new_y }) == 0 && (coords.y - new_y) >= minCoord.y)
	{
		
		if (std::any_of(EnemyTargetList.begin(), EnemyTargetList.end(), [&](const Coords rhs) {
			return rhs != Coords{coords.x, coords.y - new_y }; }))
			{
				moves.push_back(std::make_pair(coords, Coords{ coords.x,coords.y - new_y }));
				myTargetList.push_back({ coords.x,coords.y - new_y });
			}
		
	}
	
	//Check down
	if (mypieces->count({ coords.x,coords.y + new_y }) == 0 && (coords.y + new_y) <= maxCoord.y)
	{
		for (const auto& m : EnemyTargetList)
		{
			if (std::any_of(EnemyTargetList.begin(), EnemyTargetList.end(), [&](const Coords rhs) {
				return rhs != Coords{coords.x, coords.y + new_y}; }))
			{
				moves.push_back(std::make_pair(coords, Coords{ coords.x,coords.y + new_y }));
				myTargetList.push_back({ coords.x,coords.y + new_y });
			}
		}
	}
}
