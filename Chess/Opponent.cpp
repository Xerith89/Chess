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
	std::uniform_int_distribution<int> distribution(0, 7);
	int maximum = 0;
	int x_roll = distribution(rng);
	int y_roll = distribution(rng);

	while (maximum < 1)
	{
		x_roll = distribution(rng);
		y_roll = distribution(rng);

		if (brd.blackPieces.count({ x_roll,y_roll }) > 0)
		{
			brd.blackPieces.find({ x_roll,y_roll })->second->GetMoves(&brd.blackPieces, &brd.whitePieces);

			maximum = brd.blackPieces.find({ x_roll,y_roll })->second->MoveList().size() - 1;
		}
	}
		
	std::uniform_int_distribution<int> movepick(0, std::max(0,maximum));
	
	int move_roll = movepick(rng);
	brd.blackPieces.find({ x_roll,y_roll })->second->MoveTo(brd.blackPieces.find({ x_roll,y_roll })->second->MoveList().at(move_roll));
	auto newloc = brd.blackPieces.find({ x_roll,y_roll })->second->MoveList().at(move_roll);
	brd.blackPieces.insert_or_assign({ newloc.x, newloc.y }, std::move(brd.blackPieces.find({ x_roll,y_roll })->second));
	brd.blackPieces.erase({ x_roll,y_roll });
	if (brd.whitePieces.count({ newloc.x, newloc.y }) > 0)
	{
		brd.whitePieces.erase({ newloc.x,newloc.y });
	}
}
