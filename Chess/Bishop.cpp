#include "Bishop.h"
#include "Board.h"
Bishop::Bishop(int x, int y, const std::string spritename, bool white, Board& brd)
	:
	Piece({ x,y }, spritename,brd,white)
{
}

std::vector<std::pair<Coords, Coords>> Bishop::GetMoves()
{
	if (whitePiece)
	{
		myKingPos = brd.GetWhiteKingLoc();
		myPieces = &brd.whitePieces;
		opponentKingPos = brd.GetBlackKingLoc();
		opponentPieces = &brd.blackPieces;
	}
	else
	{		
		myKingPos = brd.GetBlackKingLoc();
		myPieces = &brd.blackPieces;
		opponentKingPos = brd.GetWhiteKingLoc();
		opponentPieces = &brd.whitePieces;
	}
	
	std::vector<std::pair<Coords, Coords>> moves;

	int new_x = 1;
	int new_y = 1;
	//Check pieces left up - we don't want to go past our white pieces or the end of the board
	while (myPieces->count({ coords.x - new_x,coords.y - new_y }) == 0 && (coords.x - new_x) >= minCoord.x 
		&& (coords.y - new_y) >= minCoord.y)
	{
		if (Coords{ coords.x - new_x, coords.y - new_y } != opponentKingPos)
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x - new_x,coords.y - new_y }));
		}
		myTargetList.insert(Coords{ coords.x - new_x,coords.y - new_y });
		
		if (opponentPieces->count({ coords.x - new_x, coords.y- new_y }) > 0)
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
		myTargetList.insert(Coords{ coords.x + new_x,coords.y + new_y } );
		
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

std::vector<std::pair<Coords, Coords>> Bishop::GetCheckedMoves()
{

	std::vector<std::pair<Coords, Coords>> trimMoves;
	/*
	for each move we're processing, pretend that we've made it then run get targets
	check if king loc is still equal to a target. If so then its not a valid move
	If it isn't then it is a valid move and we had it to the returned move vector.
	*/
	return trimMoves;
}


