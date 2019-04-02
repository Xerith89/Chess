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

bool Opponent::GetCmated() const
{
	return cmated;
}

void Opponent::TestForCheck()
{
	//Go through the possible targets of the white pieces and see if we're checked.
	for (const auto& m : brd.whitePieceTargets)
	{
		if (m == brd.GetBlackKingLoc())
		{
			checked = true;
			return;
		}
	}
	checked = false;
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

		TestForCheck();
		//If we find a piece with the random X and Y, get the moves for it.
		auto piece = brd.blackPieces.find({ x_roll,y_roll });
		
		if (piece != brd.blackPieces.end())
		{
			
			(!checked)? movelist = piece->second->GetMoves(&brd.blackPieces, &brd.whitePieces, brd.blackPieceTargets, brd.GetWhiteKingLoc(), brd.whitePieceTargets, brd.GetBlackKingLoc())
			: movelist = piece->second->GetCheckedMoves(&brd.blackPieces, &brd.whitePieces, brd.blackPieceTargets, brd.GetWhiteKingLoc(), brd.whitePieceTargets, brd.GetBlackKingLoc());
			if (checked)
			{
				piece = brd.blackPieces.find({ brd.GetBlackKingLoc().x,brd.GetBlackKingLoc().y });
				movelist = piece->second->GetCheckedMoves(&brd.blackPieces, &brd.whitePieces, brd.blackPieceTargets, brd.GetWhiteKingLoc(), brd.whitePieceTargets, brd.GetBlackKingLoc());
				if (movelist.size() == 0)
				{
					cmated = true;
					return;
			}
			}
			maximum = movelist.size() - 1;
			//Set maximum to be the amount of moves in the list. If its 0 then we run the loop again
		}
	}
	
	//Pick a random move by getting a number between 0 and max, it will act as the index into the moves vector
	std::uniform_int_distribution<int> movepick(0, std::max(0,maximum));
	int move_roll = movepick(rng);
	auto piece = brd.blackPieces.find({ x_roll,y_roll });
	//Index into the moves list
	piece->second->MoveTo(movelist.at(move_roll).second);
	//Set the new position
	auto newloc = movelist.at(move_roll).second;
	//Reinsert into the map at the new position, remove the old entry
	brd.blackPieces.insert_or_assign({ newloc.x, newloc.y }, std::move(piece->second));
	brd.blackPieces.erase({ x_roll,y_roll });
	//Check if we're moving our king, if so then update the king's position
	kingInstance = dynamic_cast<King*>(brd.blackPieces.find({ newloc.x, newloc.y })->second.get());
	if (kingInstance != nullptr)
	{
		brd.UpdateBlackKingLoc( { newloc.x,newloc.y });
	}
	
	//If we take a piece then update that too
	if (brd.whitePieces.count({ newloc.x, newloc.y }) > 0)
	{
		brd.whitePieces.erase({ newloc.x,newloc.y });
	}
	//recalculate our targets following our turn
	brd.blackPieceTargets.clear();
	for (const auto& p : brd.blackPieces)
	{
		p.second->GetMoves(&brd.blackPieces, &brd.whitePieces, brd.blackPieceTargets, brd.GetWhiteKingLoc(), brd.whitePieceTargets, brd.GetBlackKingLoc());
	}
}
