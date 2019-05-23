#include "Bishop.h"
#include "Board.h"

Bishop::Bishop(int x, int y, const std::string spritename, bool white, Board& brd)
	:
	Piece({ x,y }, spritename,brd,white)
{
	if (white && x == 5)
	{
		blackSquare = true;
	}
	else if (!white && x == 2)
	{
		blackSquare = true;
	}
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
	while (myPieces->count({ coords.x - new_x,coords.y - new_y }) == 0 && (coords.x - new_x) >= minCoord.x && (coords.y - new_y) >= minCoord.y)
	{
		if (Coords{ coords.x - new_x, coords.y - new_y } != opponentKingPos && brd.CheckValidMove(coords, Coords{ coords.x - new_x, coords.y - new_y }, whitePiece))
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x - new_x,coords.y - new_y }));
		}
		
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
	while (myPieces->count({ coords.x + new_x,coords.y - new_y }) == 0 && (coords.x + new_x) <= maxCoord.x && (coords.y - new_y) >= minCoord.y)
	{
		if (Coords{ coords.x + new_x,coords.y - new_y } != opponentKingPos && brd.CheckValidMove(coords, Coords{ coords.x + new_x,coords.y - new_y }, whitePiece))
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x + new_x,coords.y - new_y }));
		}
		
		if (opponentPieces->count({ coords.x + new_x,coords.y - new_y }) > 0)
		{
			break;
		}
		new_x++;
		new_y++;
	}

	new_x = 1;
	new_y = 1;
	//Check pieces right down - we don't want to go past our white pieces or the end of the board
	while (myPieces->count({ coords.x + new_x,coords.y + new_y }) == 0 && (coords.x + new_x) <= maxCoord.x && (coords.y + new_y) <= maxCoord.y)
	{
		if (Coords{ coords.x + new_x,coords.y + new_y } != opponentKingPos && brd.CheckValidMove(coords, Coords{ coords.x + new_x,coords.y + new_y }, whitePiece))
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x + new_x,coords.y + new_y }));
		}
				
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
	while (myPieces->count({ coords.x - new_x,coords.y + new_y }) == 0 && (coords.x - new_x) >= minCoord.x && (coords.y + new_y) <= maxCoord.y)
	{
		if (Coords{ coords.x - new_x,coords.y + new_y } != opponentKingPos && brd.CheckValidMove(coords, Coords{ coords.x - new_x,coords.y + new_y }, whitePiece))
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x - new_x,coords.y + new_y }));
		}
		
		if (opponentPieces->count({ coords.x - new_x, coords.y + new_y }) > 0)
		{
			break;
		}
		new_x++;
		new_y++;
	}

	return moves;
}

void Bishop::GetTargets(Map* oppoPieces)
{
	myTargetList.clear();
	opponentPieces = oppoPieces;
	if (whitePiece)
	{
		myKingPos = brd.GetWhiteKingLoc();
		myPieces = &brd.whitePieces;
		opponentKingPos = brd.GetBlackKingLoc();
	}
	else
	{
		myKingPos = brd.GetBlackKingLoc();
		myPieces = &brd.blackPieces;
		opponentKingPos = brd.GetWhiteKingLoc();
	}

	int new_x = 1;
	int new_y = 1;
	//Check targets left up
	while (opponentPieces->count({ coords.x,coords.y }) == 0  && (coords.x - new_x) >= minCoord.x && (coords.y - new_y) >= minCoord.y)
	{
		//insert the target into our target list
		myTargetList.insert(Coords{ coords.x - new_x,coords.y - new_y });
		//If we hit our player then add it as a target and break
		if (myPieces->count({ coords.x - new_x,coords.y - new_y }) > 0)
		{
			break;
		}
		//if we encounter an opponent check if it is a king - break if it isn't
		if (opponentPieces->count({ coords.x - new_x, coords.y - new_y }) > 0 && opponentKingPos != Coords{ coords.x - new_x, coords.y - new_y })
		{
			break;	
		}
		//otherwise keep going
		new_x++;
		new_y++;
	}

	new_x = 1;
	new_y = 1;
	//Check pieces right up 
	while (opponentPieces->count({ coords.x,coords.y }) == 0 && (coords.x + new_x) <= maxCoord.x && (coords.y - new_y) >= minCoord.y)
	{
		myTargetList.insert(Coords{ coords.x + new_x,coords.y - new_y });
		
		if (myPieces->count({ coords.x + new_x,coords.y - new_y }) > 0)
		{
			break;
		}

		if (opponentPieces->count({ coords.x + new_x, coords.y - new_y }) > 0 && opponentKingPos != Coords{ coords.x + new_x, coords.y - new_y })
		{
			break;
		}
		new_x++;
		new_y++;
	}

	new_x = 1;
	new_y = 1;
	//Check pieces right down 
	while (opponentPieces->count({ coords.x,coords.y }) == 0 && (coords.x + new_x) <= maxCoord.x && (coords.y + new_y) <= maxCoord.y)
	{
		myTargetList.insert(Coords{ coords.x + new_x,coords.y + new_y });

		if (myPieces->count({ coords.x + new_x,coords.y + new_y }) > 0)
		{
			break;
		}

		if (opponentPieces->count({ coords.x + new_x, coords.y + new_y }) > 0 && opponentKingPos != Coords{ coords.x + new_x, coords.y + new_y })
		{
			break;
		}
		new_x++;
		new_y++;
	}

	new_x = 1;
	new_y = 1;
	//Check pieces left down
	while (opponentPieces->count({ coords.x,coords.y }) == 0 && (coords.x - new_x) >= minCoord.x && (coords.y + new_y) <= maxCoord.y)
	{
		myTargetList.insert(Coords{ coords.x - new_x,coords.y + new_y });
		
		if (myPieces->count({ coords.x - new_x,coords.y + new_y }) > 0)
		{
			break;
		}

		if (opponentPieces->count({ coords.x - new_x, coords.y + new_y }) > 0 && opponentKingPos != Coords{ coords.x - new_x, coords.y + new_y })
		{
			break;
		}
		new_x++;
		new_y++;
	}

	//add our targets to the main target list
	if (whitePiece)
	{
		brd.whitePieceTargets.insert(myTargetList.begin(), myTargetList.end());
	}
	else
	{
		brd.blackPieceTargets.insert(myTargetList.begin(), myTargetList.end());
	}
}

int Bishop::GetScore()
{
	return score;
}

bool Bishop::GetBlackSquare() const
{
	return blackSquare;
}

int Bishop::GetBetterScore()
{
	int bestScore = score;

	bestScore += boardPositionValue.at(coords.y * 8 + coords.x);

	return bestScore;
}



