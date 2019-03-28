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
		if (brd.blackPieces.count({ x_roll,y_roll }) > 0)
		{
			brd.blackPieces.find({ x_roll,y_roll })->second->GetMoves(&brd.blackPieces, &brd.whitePieces);
			//Set maximum to be the amount of moves in the list. If its 0 then we run the loop again
			maximum = brd.blackPieces.find({ x_roll,y_roll })->second->MoveList().size() - 1;
		}
	}
	
	//Pick a random move by getting a number between 0 and max, it will act as the index into the moves vector
	std::uniform_int_distribution<int> movepick(0, std::max(0,maximum));
	int move_roll = movepick(rng);

	//Index into the moves list
	brd.blackPieces.find({ x_roll,y_roll })->second->MoveTo(brd.blackPieces.find({ x_roll,y_roll })->second->MoveList().at(move_roll));
	//Set the new position
	auto newloc = brd.blackPieces.find({ x_roll,y_roll })->second->MoveList().at(move_roll);
	//Reinsert into the map at the new position, remove the old entry
	brd.blackPieces.insert_or_assign({ newloc.x, newloc.y }, std::move(brd.blackPieces.find({ x_roll,y_roll })->second));
	brd.blackPieces.erase({ x_roll,y_roll });
	//Check if we're moving our king, if so then update the king's position
	kingInstance = dynamic_cast<King*>(brd.blackPieces.find({ newloc.x, newloc.y })->second.get());
	if (kingInstance != nullptr)
	{
		kingLoc = { newloc.x,newloc.y };
		kingInstance = nullptr;
	}
	//If we take a piece then update that too
	if (brd.whitePieces.count({ newloc.x, newloc.y }) > 0)
	{
		brd.whitePieces.erase({ newloc.x,newloc.y });
	}
}

Coords Opponent::GetKingPosition() const
{
	return kingLoc;
}
