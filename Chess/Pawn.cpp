#include "Pawn.h"

Pawn::Pawn(int x, int y, const std::string spritename, bool white, const Board& brd)
	:
	Piece({ x,y }, spritename, brd),
	whitePiece(white)
{
	startCoords = { x,y };
}

std::vector<std::pair<Coords, Coords>> Pawn::GetMoves(const Map* mypieces, const Map* opponentpieces, std::set<Coords>& myTargetList, const Coords& enemyKingPos, std::set<Coords>& EnemyTargetList, const Coords & myKingPos)
{
	//Empty out the moves list from the previous piece
	std::vector<std::pair<Coords, Coords>> moves;
	y_offset = 1;
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
		if (Coords{ coords.x - 1,coords.y - attackOffset } != enemyKingPos)
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x - 1,coords.y - attackOffset }));
		}
		
	}
		
	if (!whitePiece)
	{
		myTargetList.insert(Coords{ coords.x - 1,coords.y + 1 });
		myTargetList.insert(Coords{ coords.x + 1,coords.y + 1 });
	}
	else
	{
		myTargetList.insert(Coords{ coords.x - 1,coords.y - 1 });
		myTargetList.insert(Coords{ coords.x + 1,coords.y - 1 });
	}
	
	if (opponentpieces->count({ coords.x + 1,coords.y - attackOffset }) == 1)
	{
		assert(y_offset < 10);
		if (Coords{ coords.x + 1,coords.y - attackOffset } != enemyKingPos)
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x + 1,coords.y - attackOffset }));
		}
		
	}
	return moves;
}

std::vector<std::pair<Coords, Coords>> Pawn::GetCheckedMoves(const Map* mypieces, const Map* opponentpieces, std::set<Coords>& myTargetList, const Coords& enemyKingPos, std::set<Coords>& EnemyTargetList, const Coords & myKingPos)
{
	//Get every available move;
	auto allMoves = GetMoves(mypieces, opponentpieces, myTargetList, enemyKingPos, EnemyTargetList, myKingPos);
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

