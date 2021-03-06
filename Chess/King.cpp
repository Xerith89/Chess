#include "King.h"
#include "Board.h"

King::King(int x, int y, const std::string spritename,bool white, Board& brd)
	:
	Piece({ x,y }, spritename, brd, white)
{
}

std::vector<std::pair<Coords, Coords>> King::GetMoves()
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
	int new_y = 1;
	//Check pieces left up - we don't want to go past our white pieces or the end of the board
	if (myPieces->count({ coords.x - new_x,coords.y - new_y }) == 0 && (coords.x - new_x) >= minCoord.x
		&& (coords.y - new_y) >= minCoord.y && Coords{ coords.x - new_x,coords.y - new_y } != opponentKingPos
		&& coords.y - new_y != (opponentKingPos.y+new_y || opponentKingPos.y || opponentKingPos.y-new_y) && coords.x - new_x != (opponentKingPos.x|| opponentKingPos.x-new_x ||opponentKingPos.x+new_x))
	{
		if (std::none_of(opponentTargetList.begin(), opponentTargetList.end(), [&](const Coords rhs) {
			return rhs == Coords{ coords.x - new_x,coords.y - new_y }; }))
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x - new_x,coords.y - new_y }));
			myTargetList.insert(Coords{ coords.x - new_x,coords.y - new_y });
		}
	}

	
	//Check pieces right up - we don't want to go past our white pieces or the end of the board
	if (myPieces->count({ coords.x + new_x,coords.y - new_y }) == 0 && (coords.x + new_x) <= maxCoord.x
		&& (coords.y - new_y) >= minCoord.y && Coords{ coords.x + new_x,coords.y - new_y } != opponentKingPos
		&& coords.y - new_y != (opponentKingPos.y + new_y || opponentKingPos.y || opponentKingPos.y - new_y) && coords.x - new_x != (opponentKingPos.x || opponentKingPos.x - new_x || opponentKingPos.x + new_x))
	{
		if (std::none_of(opponentTargetList.begin(), opponentTargetList.end(), [&](const Coords rhs) {
			return rhs == Coords{ coords.x + new_x,coords.y - new_y }; }))
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x + new_x,coords.y - new_y }));
			myTargetList.insert(Coords{ coords.x + new_x,coords.y - new_y });
		}
	}

	//Check pieces right down - we don't want to go past our white pieces or the end of the board
	if (myPieces->count({ coords.x + new_x,coords.y + new_y }) == 0 && (coords.x + new_x) <= maxCoord.x
		&& (coords.y + new_y) <= maxCoord.y && Coords{ coords.x + new_x,coords.y + new_y } != opponentKingPos
		&& coords.y - new_y != (opponentKingPos.y + new_y || opponentKingPos.y || opponentKingPos.y - new_y) && coords.x - new_x != (opponentKingPos.x || opponentKingPos.x - new_x || opponentKingPos.x + new_x))
	{
		if (std::none_of(opponentTargetList.begin(), opponentTargetList.end(), [&](const Coords rhs) {
		return rhs == Coords{ coords.x + new_x,coords.y + new_y }; }))
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x + new_x,coords.y + new_y }));
			myTargetList.insert(Coords{ coords.x + new_x,coords.y + new_y });
		}
		
	}

	//Check pieces left down - we don't want to go past our white pieces or the end of the board
	if (myPieces->count({ coords.x - new_x,coords.y + new_y }) == 0 && (coords.x - new_x) >= minCoord.x
		&& (coords.y + new_y) <= maxCoord.y && Coords{ coords.x - new_x,coords.y + new_y } != opponentKingPos
		&& coords.y - new_y != (opponentKingPos.y + new_y || opponentKingPos.y || opponentKingPos.y - new_y) && coords.x - new_x != (opponentKingPos.x || opponentKingPos.x - new_x || opponentKingPos.x + new_x))
	{
		if (std::none_of(opponentTargetList.begin(), opponentTargetList.end(), [&](const Coords rhs) {
			return rhs == Coords{ coords.x - new_x,coords.y + new_y }; }))
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x - new_x,coords.y + new_y }));
			myTargetList.insert(Coords{ coords.x - new_x,coords.y + new_y });
		}
	}

	//check left
	if (myPieces->count({ coords.x - new_x,coords.y }) == 0 && (coords.x - new_x) >= minCoord.x && Coords{ coords.x - new_x,coords.y } != opponentKingPos
		&& coords.y - new_y != (opponentKingPos.y + new_y || opponentKingPos.y || opponentKingPos.y - new_y) && coords.x - new_x != (opponentKingPos.x || opponentKingPos.x - new_x || opponentKingPos.x + new_x))
	{
		if (std::none_of(opponentTargetList.begin(), opponentTargetList.end(), [&](const Coords rhs) {
			return rhs == Coords{ coords.x - new_x,coords.y }; }))
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x - new_x,coords.y }));
			myTargetList.insert(Coords{ coords.x - new_x,coords.y });
		}
	}

	if (brd.GetLeftCastling())
	{
		moves.push_back(std::make_pair(coords, Coords{ coords.x - 2,coords.y }));
		myTargetList.insert(Coords{ coords.x - 2,coords.y });
	}
	if (brd.GetRightCastling())
	{
		moves.push_back(std::make_pair(coords, Coords{ coords.x + 2,coords.y }));
		myTargetList.insert(Coords{ coords.x + 2,coords.y });
	}
	//check right
	if (myPieces->count({ coords.x + new_x,coords.y }) == 0 && (coords.x + new_x) <= maxCoord.x && Coords{ coords.x + new_x,coords.y } != opponentKingPos
		&& coords.y - new_y != (opponentKingPos.y + new_y || opponentKingPos.y || opponentKingPos.y - new_y) && coords.x - new_x != (opponentKingPos.x || opponentKingPos.x - new_x || opponentKingPos.x + new_x))
	{
		if (std::none_of(opponentTargetList.begin(), opponentTargetList.end(), [&](const Coords rhs) {
		return rhs == Coords{ coords.x + new_x,coords.y }; }))
		{
			moves.push_back(std::make_pair(coords, Coords{ coords.x + new_x,coords.y }));
			myTargetList.insert(Coords{ coords.x + new_x,coords.y });
		}
		
	}

	//check up
	if (myPieces->count({ coords.x,coords.y - new_y }) == 0 && (coords.y - new_y) >= minCoord.y && Coords{ coords.x,coords.y - new_y } != opponentKingPos
		&& coords.y - new_y != (opponentKingPos.y + new_y || opponentKingPos.y || opponentKingPos.y - new_y) && coords.x - new_x != (opponentKingPos.x || opponentKingPos.x - new_x || opponentKingPos.x + new_x))
	{
		
		if (std::none_of(opponentTargetList.begin(), opponentTargetList.end(), [&](const Coords rhs) {
			return rhs == Coords{coords.x, coords.y - new_y }; }))
			{
				moves.push_back(std::make_pair(coords, Coords{ coords.x,coords.y - new_y }));
				myTargetList.insert(Coords{ coords.x,coords.y - new_y });
			}
		
	}
	
	//Check down
	if (myPieces->count({ coords.x,coords.y + new_y }) == 0 && (coords.y + new_y) <= maxCoord.y && Coords{ coords.x,coords.y + new_y} != opponentKingPos
		&& coords.y - new_y != (opponentKingPos.y + new_y || opponentKingPos.y || opponentKingPos.y - new_y) && coords.x - new_x != (opponentKingPos.x || opponentKingPos.x - new_x || opponentKingPos.x + new_x))
	{
		if (std::none_of(opponentTargetList.begin(), opponentTargetList.end(), [&](const Coords rhs) {
			return rhs == Coords{coords.x, coords.y + new_y}; }))
		{
				moves.push_back(std::make_pair(coords, Coords{ coords.x,coords.y + new_y }));
				myTargetList.insert(Coords{ coords.x,coords.y + new_y });
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

	return moves;
}

void King::GetTargets(Map* oppoPieces)
{
	myTargetList.clear();
	GetMoves();
}

int King::GetScore()
{
	return score;
}

int King::GetBetterScore()
{
	int bestScore = score;

	if (brd.blackPieces.size() > 6)
	{
		bestScore += boardPositionValue.at(coords.y * 8 + coords.x);
	}
	else
	{
		bestScore += endBoardPositionValue.at(coords.y * 8 + coords.x);
	}

	return bestScore;
}


