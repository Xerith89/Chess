#include "Rook.h"
#include "Board.h"
Rook::Rook(int x, int y, const std::string spritename,bool white, Board& brd)
	:
	Piece({ x,y }, spritename, brd, white)
{
}

std::vector<std::pair<Coords, Coords>> Rook::GetMoves()
{
	if (whitePiece)
	{
		myKingPos = brd.GetWhiteKingLoc();
		myPieces = &brd.whitePieces;
		myTargetList = brd.whitePieceTargets;
		opponentKingPos = brd.GetBlackKingLoc();
		opponentPieces = &brd.blackPieces;
		opponentTargetList = brd.blackPieceTargets;
	}
	else
	{
		myKingPos = brd.GetBlackKingLoc();
		myPieces = &brd.blackPieces;
		myTargetList = brd.blackPieceTargets;
		opponentKingPos = brd.GetWhiteKingLoc();
		opponentPieces = &brd.whitePieces;
		opponentTargetList = brd.whitePieceTargets;
	}

	std::vector<std::pair<Coords, Coords>> moves;
	int new_x = 1;
	//Check pieces to our left - we don't want to go past our white pieces or the end of the board
	while (myPieces->count({ coords.x - new_x,coords.y }) == 0 && (coords.x - new_x) >= minCoord.x)
	{
		if (Coords{ coords.x - new_x,coords.y } != opponentKingPos)
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x - new_x,coords.y }));
		}
		myTargetList.insert(Coords{ coords.x - new_x,coords.y });
		
		if (opponentPieces->count({ coords.x - new_x, coords.y }) > 0)
		{break;}
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
		{break;}
		new_x++;
	
		
	}
	
	//check up
	int new_y = 1;
	while (myPieces->count({ coords.x,coords.y - new_y}) == 0 && (coords.y-new_y) >= minCoord.y)
	{
		if (Coords{ coords.x,coords.y - new_y } != opponentKingPos)
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x,coords.y - new_y }));
		}
		myTargetList.insert(Coords{ coords.x,coords.y - new_y });
		
		if (opponentPieces->count({ coords.x,coords.y - new_y }) > 0)
		{break;}
		new_y++;
	}
	//Check down
	new_y = 1;
	while (myPieces->count({ coords.x,coords.y + new_y }) == 0 && (coords.y +new_y) <= maxCoord.y)
	{
		if (Coords{ coords.x,coords.y + new_y } != opponentKingPos)
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x,coords.y + new_y }));
		}
		myTargetList.insert(Coords{ coords.x,coords.y + new_y });
		
		if (opponentPieces->count({ coords.x,coords.y + new_y }) > 0)
		{break;}
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

std::vector<std::pair<Coords, Coords>> Rook::GetCheckedMoves()
{
	std::vector<std::pair<Coords, Coords>> trimMoves;
	/*
	for each move we're processing, pretend that we've made it then run get targets
	check if king loc is still equal to a target. If so then its not a valid move
	If it isn't then it is a valid move and we had it to the returned move vector.
	*/
	return trimMoves;
}
