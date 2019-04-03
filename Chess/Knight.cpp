#include "Knight.h"
#include "Board.h"
Knight::Knight(int x, int y, const std::string spritename,bool white,  Board& brd)
	:
	Piece({ x,y }, spritename, brd, white)
{
}

std::vector<std::pair<Coords, Coords>> Knight::GetMoves()
{

	if (whitePiece)
	{
		myKingPos = brd.GetWhiteKingLoc();
		myPieces = &brd.whitePieces;
		opponentKingPos = brd.GetBlackKingLoc();
		opponentPieces = &brd.blackPieces;
		opponentTargetList = brd.blackPieceTargets;
	}
	else
	{
		myKingPos = brd.GetBlackKingLoc();
		myPieces = &brd.blackPieces;
		opponentKingPos = brd.GetWhiteKingLoc();
		opponentPieces = &brd.whitePieces;
		opponentTargetList = brd.whitePieceTargets;
	}

	std::vector<std::pair<Coords, Coords>> moves;

	int new_x = 1;
	int new_y = 2;

	//check up
	if (myPieces->count({ coords.x - new_x,coords.y - new_y }) == 0 && (coords.y - new_y) >= minCoord.y 
		&& (coords.x - new_x) >= minCoord.x)
	{
		if (Coords{ coords.x - new_x,coords.y - new_y } != opponentKingPos)
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x - new_x,coords.y - new_y }));
		}
		myTargetList.insert(Coords{ coords.x - new_x,coords.y - new_y });
	}

	if (myPieces->count({ coords.x + new_x,coords.y - new_y }) == 0 && (coords.y - new_y) >= minCoord.y
		&& (coords.x + new_x) <= maxCoord.x)
	{
		if (Coords{ coords.x + new_x,coords.y - new_y } != opponentKingPos)
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x + new_x,coords.y - new_y }));
		}
		myTargetList.insert(Coords{ coords.x + new_x,coords.y - new_y });
	}

	//check down
	if (myPieces->count({ coords.x - new_x,coords.y + new_y }) == 0 && (coords.y + new_y) <= maxCoord.y
		&& (coords.x - new_x) >= minCoord.x)
	{
		if (Coords{ coords.x - new_x,coords.y + new_y } != opponentKingPos)
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x - new_x,coords.y + new_y }));
		}
		myTargetList.insert(Coords{ coords.x - new_x,coords.y + new_y });
	}

	if (myPieces->count({ coords.x + new_x,coords.y + new_y }) == 0 && (coords.y + new_y) <= maxCoord.y
		&& (coords.x + new_x) <= maxCoord.x)
	{
		if (Coords{ coords.x + new_x,coords.y + new_y } != opponentKingPos)
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x + new_x,coords.y + new_y }));
		}
		myTargetList.insert(Coords{ coords.x + new_x,coords.y + new_y });
	}

	//check left
	new_x = 2;
	new_y = 1;

	if (myPieces->count({ coords.x - new_x,coords.y + new_y }) == 0 && (coords.y + new_y) <= maxCoord.y
		&& (coords.x - new_x) >= minCoord.x)
	{
		if (Coords{ coords.x - new_x,coords.y + new_y } != opponentKingPos)
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x - new_x,coords.y + new_y }));
		}
		myTargetList.insert(Coords{ coords.x - new_x,coords.y + new_y });
	}

	if (myPieces->count({ coords.x - new_x,coords.y - new_y }) == 0 && (coords.y - new_y) >= minCoord.y
		&& (coords.x - new_x) >= minCoord.x)
	{
		if (Coords{ coords.x - new_x,coords.y - new_y } != opponentKingPos)
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x - new_x,coords.y - new_y }));
		}
		myTargetList.insert(Coords{ coords.x - new_x,coords.y - new_y });
	}

	if (myPieces->count({ coords.x + new_x,coords.y + new_y }) == 0 && (coords.y + new_y) <= maxCoord.y
		&& (coords.x + new_x) <= maxCoord.x)
	{
		if (Coords{ coords.x + new_x,coords.y + new_y } != opponentKingPos)
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x + new_x,coords.y + new_y }));
		}
		myTargetList.insert(Coords{ coords.x + new_x,coords.y + new_y });
	}

	if (myPieces->count({ coords.x + new_x,coords.y - new_y }) == 0 && (coords.y - new_y) >= minCoord.y
		&& (coords.x + new_x) <= maxCoord.x)
	{
		if (Coords{ coords.x + new_x,coords.y - new_y } != opponentKingPos)
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x + new_x,coords.y - new_y }));
		}
		myTargetList.insert(Coords{ coords.x + new_x,coords.y - new_y });
	}

	if (whitePiece)
	{
		brd.whitePieceTargets.insert(myTargetList.begin(), myTargetList.end());
	}
	else
	{
		brd.blackPieceTargets.insert(myTargetList.begin(), myTargetList.end());
	}
	return moves;
}

