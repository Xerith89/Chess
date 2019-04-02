#include "Queen.h"
#include "Board.h"
Queen::Queen(int x, int y, const std::string spritename,bool white, const Board& brd)
	:
	Piece({ x,y }, spritename, brd, white)
{
}

std::vector<std::pair<Coords, Coords>> Queen::GetMoves()
{
	if (whitePiece)
	{
		myKingPos = brd.GetWhiteKingLoc();
		myPieces = &brd.whitePieces;
		myTargetList = brd.whitePieceTargets;
		opponentKingPos = brd.GetBlackKingLoc();
		opponentPieces = &brd.blackPieces;
		opponentTargetList = &brd.blackPieceTargets;
	}
	else
	{
		myKingPos = brd.GetBlackKingLoc();
		myPieces = &brd.blackPieces;
		myTargetList = brd.blackPieceTargets;
		opponentKingPos = brd.GetWhiteKingLoc();
		opponentPieces = &brd.whitePieces;
		opponentTargetList = &brd.whitePieceTargets;
	}

	std::vector<std::pair<Coords, Coords>> moves;

	int new_x = 1;
	int new_y = 1;
	//Check pieces left up - we don't want to go past our white pieces or the end of the board
	while (myPieces->count({ coords.x - new_x,coords.y - new_y }) == 0 && (coords.x - new_x) >= minCoord.x
		&& (coords.y - new_y) >= minCoord.y)
	{
		if (Coords{ coords.x - new_x,coords.y - new_y } != opponentKingPos)
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x - new_x,coords.y - new_y }));
		}
		myTargetList.insert(Coords{ coords.x - new_x,coords.y - new_y });

		if (opponentPieces->count({ coords.x - new_x, coords.y - new_y }) > 0)
		{
			break;
		}
		new_x++;
		new_y++;
	}

	new_x = 1;
	new_y = 1;
	//Check pieces right up - we don't want to go past our white pieces or the end of the board
	while (myPieces->count({ coords.x + new_x,coords.y - new_y }) == 0 && (coords.x + new_x) <= maxCoord.x
		&& (coords.y - new_y) >= minCoord.y)
	{
		if (Coords{ coords.x + new_x,coords.y - new_y } != opponentKingPos)
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x + new_x,coords.y - new_y }));
		}
		myTargetList.insert(Coords{ coords.x + new_x,coords.y - new_y });
		
		if (opponentPieces->count({ coords.x + new_x, coords.y - new_y }) > 0)
		{
			break;
		}
		new_x++;
		new_y++;
	}

	new_x = 1;
	new_y = 1;
	//Check pieces right down - we don't want to go past our white pieces or the end of the board
	while (myPieces->count({ coords.x + new_x,coords.y + new_y }) == 0 && (coords.x + new_x) <= maxCoord.x
		&& (coords.y + new_y) <= maxCoord.y)
	{
		if (Coords{ coords.x + new_x,coords.y + new_y } != opponentKingPos)
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x + new_x,coords.y + new_y }));
		}
		myTargetList.insert(Coords{ coords.x + new_x,coords.y + new_y });
	
		if (opponentPieces->count({ coords.x + new_x, coords.y + new_y }) > 0)
		{
			break;
		}
		new_x++;
		new_y++;
	}

	new_x = 1;
	new_y = 1;
	//Check pieces left down - we don't want to go past our white pieces or the end of the board
	while (myPieces->count({ coords.x - new_x,coords.y + new_y }) == 0 && (coords.x - new_x) >= minCoord.x
		&& (coords.y + new_y) <= maxCoord.y)
	{
		if (Coords{ coords.x - new_x,coords.y + new_y } != opponentKingPos)
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x - new_x,coords.y + new_y }));
		}
		myTargetList.insert(Coords{ coords.x - new_x,coords.y + new_y });
		
		if (opponentPieces->count({ coords.x - new_x, coords.y + new_y }) > 0)
		{
			break;
		}
		new_x++;
		new_y++;
	}

	while (myPieces->count({ coords.x - new_x,coords.y }) == 0 && (coords.x - new_x) >= minCoord.x)
	{
		if (Coords{ coords.x - new_x,coords.y } != opponentKingPos)
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x - new_x,coords.y }));
		}
		myTargetList.insert(Coords{ coords.x - new_x,coords.y });
		
		if (opponentPieces->count({ coords.x - new_x, coords.y }) > 0)
		{
			break;
		}
		new_x++;

	}
	//Reset x and check right
	new_x = 1;
	while (myPieces->count({ coords.x + new_x,coords.y }) == 0 && (coords.x + new_x) <= maxCoord.x)
	{
		if (Coords{ coords.x + new_x,coords.y } != opponentKingPos)
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x + new_x,coords.y }));
		}
		myTargetList.insert(Coords{ coords.x + new_x,coords.y });
		
		if (opponentPieces->count({ coords.x + new_x, coords.y }) > 0)
		{
			break;
		}
		new_x++;
	}
	
	new_x = 1;
	while (myPieces->count({ coords.x - new_x,coords.y }) == 0 && (coords.x - new_x) >= minCoord.x)
	{
		if (Coords{ coords.x - new_x,coords.y } != opponentKingPos)
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x - new_x,coords.y }));
		}
		myTargetList.insert(Coords{ coords.x - new_x,coords.y });
		
		if (opponentPieces->count({ coords.x - new_x, coords.y }) > 0)
		{
			break;
		}
		new_x++;
	}
	new_y = 1;
	//check up
	while (myPieces->count({ coords.x,coords.y - new_y }) == 0 && (coords.y - new_y) >= minCoord.y)
	{
		if (Coords{ coords.x,coords.y - new_y } != opponentKingPos)
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x,coords.y - new_y }));
		}
		myTargetList.insert({ coords.x,coords.y - new_y });
		
		if (opponentPieces->count({ coords.x,coords.y - new_y }) > 0)
		{
			break;
		}
		new_y++;
	}
	//Check down
	new_y = 1;
	while (myPieces->count({ coords.x,coords.y + new_y }) == 0 && (coords.y + new_y) <= maxCoord.y)
	{
		if (Coords{ coords.x,coords.y + new_y } != opponentKingPos)
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x,coords.y + new_y }));
		}
		myTargetList.insert(Coords{ coords.x,coords.y + new_y });
		
		if (opponentPieces->count({ coords.x,coords.y + new_y }) > 0)
		{
			break;
		}
		new_y++;
	}
	return moves;
}

std::vector<std::pair<Coords, Coords>> Queen::GetCheckedMoves()
{
	std::vector<std::pair<Coords, Coords>> trimMoves;
	/*Get every available move;
	auto allMoves = GetMoves(myPieces, opponentPieces, myTargetList, opponentKingPos, EnemyTargetList, myKingPos);

	//Go through the enemy target list and if it matches our move list then add it to the filtered move list
	for (const auto& m : EnemyTargetList)
	{
		auto it = (std::find_if(allMoves.begin(), allMoves.end(), [&](const std::pair<Coords, Coords>& rhs) {
			return m == rhs.second; }));

		if (it != allMoves.end())
		{
			trimMoves.push_back(*it);
		}
	}*/
	return trimMoves;
}
