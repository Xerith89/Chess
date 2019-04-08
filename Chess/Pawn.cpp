#include "Pawn.h"
#include "Board.h"
Pawn::Pawn(int x, int y, const std::string spritename, bool white, Board& brd)
	:
	Piece({ x,y }, spritename, brd, white)	
{
	startCoords = { x,y };
}

std::vector<std::pair<Coords, Coords>> Pawn::GetMoves()
{
	if (whitePiece)
	{
		myPieces = &brd.whitePieces;
		opponentKingPos = brd.GetBlackKingLoc();
		opponentPieces = &brd.blackPieces;
		y_offset = 1;
		attackOffset = 1;
	}
	else
	{
		myPieces = &brd.blackPieces;
		opponentKingPos = brd.GetWhiteKingLoc();
		opponentPieces = &brd.whitePieces;
		y_offset = -1;
		attackOffset = -1;
	}

	//Empty out the moves list from the previous piece
	std::vector<std::pair<Coords, Coords>> moves;
		
	//Pawns can move 2 places on the first go so check if we've moved yet
	if (coords != startCoords) 
	{ 
		firstMove = false; 
	}
	
	//If we haven't moved then we want to check if the place is free up to two times
	if (firstMove)
	{
		while (myPieces->count({ coords.x, coords.y - y_offset }) == 0 && std::abs(y_offset) < 3)
		{
			if (opponentPieces->count({ coords.x,coords.y - y_offset }) == 0 && brd.CheckValidMove(coords, Coords{ coords.x,coords.y - y_offset }, whitePiece))
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
		while (myPieces->count({ coords.x,coords.y - y_offset }) == 0 && y_offset < 2)
		{
			if (opponentPieces->count({ coords.x,coords.y - y_offset }) == 0 && brd.CheckValidMove(coords, Coords{ coords.x,coords.y - y_offset }, whitePiece))
			{
				assert(y_offset < 10);
				moves.push_back(std::make_pair(coords, Coords{ coords.x,coords.y - y_offset }));
			}
			y_offset++;
		}
	}
	
	//Check if we have any diagonal black pieces at our current space - they  can be taken and are a possible move
	if (opponentPieces->count({ coords.x - 1,coords.y - attackOffset }) == 1)
	{
		assert(y_offset < 10);
		if (Coords{ coords.x - 1,coords.y - attackOffset } != opponentKingPos && brd.CheckValidMove(coords, Coords{ coords.x - 1,coords.y - attackOffset }, whitePiece))
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x - 1,coords.y - attackOffset }));
		}
		
	}
			
	if (opponentPieces->count({ coords.x + 1,coords.y - attackOffset }) == 1)
	{
		assert(y_offset < 10);
		if (Coords{ coords.x + 1,coords.y - attackOffset } != opponentKingPos && brd.CheckValidMove(coords, Coords{ coords.x + 1,coords.y - attackOffset }, whitePiece))
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x + 1,coords.y - attackOffset }));
		}
		
	}
	if (whitePiece)
	{
		//Enpassant
		if (brd.GetBlackEnpassant() && (coords.x - 1) == brd.playedMoves.back().second.x && coords.y == brd.playedMoves.back().second.y)
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x - 1,coords.y - 1 }));
		}
		if (brd.GetBlackEnpassant() && (coords.x + 1) == brd.playedMoves.back().second.x && coords.y == brd.playedMoves.back().second.y)
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x + 1,coords.y - 1 }));
		}
	}
	else
	{
		if (brd.GetWhiteEnpassant() && (coords.x - 1) == brd.playedMoves.back().second.x && coords.y == brd.playedMoves.back().second.y)
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x - 1,coords.y + 1 }));
		}
		if (brd.GetWhiteEnpassant() && (coords.x + 1) == brd.playedMoves.back().second.x && coords.y == brd.playedMoves.back().second.y)
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x + 1,coords.y + 1 }));
		}
	}

	return moves;
}

void Pawn::GetTargets(Map* oppoPieces)
{
	(whitePiece) ?	myTargetList = brd.whitePieceTargets :	myTargetList = brd.blackPieceTargets;
	myTargetList.clear();
	if (whitePiece)
	{
		myTargetList.insert(Coords{ coords.x - 1,coords.y - 1 });
		myTargetList.insert(Coords{ coords.x + 1,coords.y - 1 });
		//Enpassant - black enpassant is true, our ycoord is equal to the y coord of the last played move
		//and our x is plus 1 or -1...add to target list
		if (brd.GetBlackEnpassant() && (coords.x - 1) == brd.playedMoves.back().second.x && coords.y == brd.playedMoves.back().second.y)
		{
			myTargetList.insert(Coords{ coords.x - 1,coords.y - 1 });
		}
		if (brd.GetBlackEnpassant() && (coords.x  +1) == brd.playedMoves.back().second.x && coords.y == brd.playedMoves.back().second.y)
		{
			myTargetList.insert(Coords{ coords.x + 1,coords.y - 1 });
		}
	}
	else
	{
		myTargetList.insert(Coords{ coords.x - 1,coords.y + 1 });
		myTargetList.insert(Coords{ coords.x + 1,coords.y + 1 });
		//Enpassant
		if (brd.GetWhiteEnpassant() && (coords.x - 1) == brd.playedMoves.back().second.x && coords.y == brd.playedMoves.back().second.y)
		{
			myTargetList.insert(Coords{ coords.x - 1,coords.y + 1 });
		}
		if (brd.GetWhiteEnpassant() && (coords.x + 1) == brd.playedMoves.back().second.x && coords.y == brd.playedMoves.back().second.y)
		{
			myTargetList.insert(Coords{ coords.x + 1,coords.y + 1 });
		}
	}

	if (whitePiece)
	{
		brd.whitePieceTargets.insert(myTargetList.begin(), myTargetList.end());		
	}
	else
	{
		brd.blackPieceTargets.insert(myTargetList.begin(), myTargetList.end());
	}
}

int Pawn::GetScore()
{
	//Early/Mid Game
	auto totalPieces = brd.blackPieces.size() + brd.whitePieces.size();
	if (brd.playedMoves.size() < 50 || totalPieces >= 20)
	{
		//Switch on the column and adjust the value for the pawn depending on the row
		//We also check for them being passed as value increases in endgame
		switch (coords.x)
		{
		case 0:
		case 7:
			if (whitePiece)
			{
				if (coords.y >= 4)
				{
					score += 90;
				}
				else if (coords.y == 3)
				{
					score += 97;
				}
				else if (coords.y < 3)
				{
					score += 106;
				}
			}
			else
			{
				if (coords.y <= 3)
				{
					score += 95;
				}
				else if (coords.y == 4)
				{
					score += 103;
				}
				else if (coords.y > 5)
				{
					score += 112;
				}
			}
			break;
		case 1:
		case 6:
			if (whitePiece)
			{
				if (coords.y >= 4)
				{
					score += 95;
				}
				else if (coords.y == 3)
				{
					score += 103;
				}
				else if (coords.y < 3)
				{
					score += 112;
				}
			}
			else
			{
				if (coords.y <= 3)
				{
					score += 95;
				}
				else if (coords.y == 4)
				{
					score += 103;
				}
				else if (coords.y > 5)
				{
					score += 112;
				}
			}
			break;
		case 2:
		case 5:
			if (whitePiece)
			{
				if (coords.y < 3)
				{
					score += 105;
				}
				else if (coords.y == 3)
				{
					score += 110;
				}
				else if (coords.y == 5)
				{
					score += 117;
				}
				else if (coords.y > 5)
				{
					score += 125;
				}
			}
			else
			{
				if (coords.y >= 5)
				{
					score += 105;
				}
				else if (coords.y == 4)
				{
					score += 110;
				}
				else if (coords.y == 3)
				{
					score += 117;
				}
				else if (coords.y < 3)
				{
					score += 125;
				}
			}
			break;
		case 3:
		case 4:
			if (whitePiece)
			{
				if (coords.y < 3)
				{
					score += 115;
				}
				else if (coords.y == 3)
				{
					score += 120;
				}
				else if (coords.y == 5)
				{
					score += 127;
				}
				else if (coords.y > 5)
				{
					score += 140;
				}
			}
			else
			{
				if (coords.y >= 5)
				{
					score += 115;
				}
				else if (coords.y == 4)
				{
					score += 120;
				}
				else if (coords.y == 3)
				{
					score += 127;
				}
				else if (coords.y < 3)
				{
					score += 140;
				}
			}
			break;
		}
	}
	else
	{
	switch (coords.x)
	{
	case 0:
	case 7:
		if (whitePiece)
		{
			if (coords.y >= 4)
			{
				score += 120;
			}
			else if (coords.y == 3)
			{
				score += 125;
			}
			else if (coords.y < 3)
			{
				score += 145;
			}
		}
		else
		{
			if (coords.y <= 3)
			{
				score += 120;
			}
			else if (coords.y == 4)
			{
				score += 125;
			}
			else if (coords.y > 5)
			{
				score += 145;
			}
		}
		break;
	case 1:
	case 6:
		if (whitePiece)
		{
			if (coords.y >= 4)
			{
				score += 110;
			}
			else if (coords.y == 3)
			{
				score += 117;
			}
			else if (coords.y < 3)
			{
				score += 129;
			}
		}
		else
		{
			if (coords.y <= 3)
			{
				score += 110;
			}
			else if (coords.y == 4)
			{
				score += 117;
			}
			else if (coords.y > 5)
			{
				score += 129;
			}
		}
		break;
	case 2:
	case 5:
		if (whitePiece)
		{
			if (coords.y < 3)
			{
				score += 95;
			}
			else if (coords.y == 3)
			{
				score += 100;
			}
			else if (coords.y == 5)
			{
				score += 107;
			}
			else if (coords.y > 5)
			{
				score += 116;
			}
		}
		else
		{
			if (coords.y >= 5)
			{
				score += 95;
			}
			else if (coords.y == 4)
			{
				score += 100;
			}
			else if (coords.y == 3)
			{
				score += 107;
			}
			else if (coords.y < 3)
			{
				score += 116;
			}
		}
		break;
	case 3:
	case 4:
		if (whitePiece)
		{
			if (coords.y < 3)
			{
				score += 90;
			}
			else if (coords.y == 3)
			{
				score += 95;
			}
			else if (coords.y == 5)
			{
				score += 100;
			}
			else if (coords.y > 5)
			{
				score += 105;
			}
		}
		else
		{
			if (coords.y >= 5)
			{
				score += 90;
			}
			else if (coords.y == 4)
			{
				score += 95;
			}
			else if (coords.y == 3)
			{
				score += 100;
			}
			else if (coords.y < 3)
			{
				score += 105;
			}
		}
		break;
	}
	}
	
	return score;
}



