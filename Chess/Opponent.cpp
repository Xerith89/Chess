#include "Opponent.h"

Opponent::Opponent(Board & brd)
	:
	brd(brd),
	rng(rd())
{
	
}

void Opponent::DoTurn()
{
	GenerationZero();
}

void Opponent::GenerationZero()
{
	//Our board positions range between 0 and 7
	std::uniform_int_distribution<int> distribution(0, 7);
	int maximum = 0;
	int x_roll;
	int y_roll;

	//Maximum starts as 0 so this loop triggers at least once
	while (maximum < 1)
	{
		x_roll = distribution(rng);
		y_roll = distribution(rng);

		//If we find a piece with the random X and Y, get the moves for it.
		auto piece = brd.blackPieces.find({ x_roll,y_roll });
		if (piece != brd.blackPieces.end())
		{
			piece->second->GetMoves(&brd.blackPieces, &brd.whitePieces, brd.blackPieceTargets, brd.GetWhiteKingLoc(),brd.whitePieceTargets);
			//Set maximum to be the amount of moves in the list. If its 0 then we run the loop again
			maximum = piece->second->MoveList().size() - 1;
		}
	}
	
	//Pick a random move by getting a number between 0 and max, it will act as the index into the moves vector
	std::uniform_int_distribution<int> movepick(0, std::max(0,maximum));
	int move_roll = movepick(rng);
	auto piece = brd.blackPieces.find({ x_roll,y_roll });
	//Index into the moves list
	piece->second->MoveTo(piece->second->MoveList().at(move_roll).second);
	//Set the new position
	auto newloc = piece->second->MoveList().at(move_roll).second;
	//Reinsert into the map at the new position, remove the old entry
	brd.blackPieces.insert_or_assign({ newloc.x, newloc.y }, std::move(piece->second));
	brd.blackPieces.erase({ x_roll,y_roll });
	//Check if we're moving our king, if so then update the king's position
	kingInstance = dynamic_cast<King*>(brd.blackPieces.find({ newloc.x, newloc.y })->second.get());
	if (kingInstance != nullptr)
	{
		brd.UpdateBlackKingLoc( { newloc.x,newloc.y });
		kingInstance = nullptr;
	}
	//If we take a piece then update that too
	if (brd.whitePieces.count({ newloc.x, newloc.y }) > 0)
	{
		brd.whitePieces.erase({ newloc.x,newloc.y });
	}
}
