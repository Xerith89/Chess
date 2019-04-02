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
	int maximum = 0;
	movelist.clear();
	TestForCheck();
	std::vector<std::pair<Coords, Coords>> temp;
	for (const auto& p : brd.blackPieces)
	{
		if (!checked) {
			temp = p.second->GetMoves(&brd.blackPieces, &brd.whitePieces, brd.blackPieceTargets, brd.GetWhiteKingLoc(), brd.whitePieceTargets, brd.GetBlackKingLoc());
		}
		else
		{
			temp = p.second->GetCheckedMoves(&brd.blackPieces, &brd.whitePieces, brd.blackPieceTargets, brd.GetWhiteKingLoc(), brd.whitePieceTargets, brd.GetBlackKingLoc());
		}
		 movelist.insert(movelist.end(), temp.begin(), temp.end()); 
	}

	if (movelist.size() == 0 && checked)
	{
		cmated = true;
		return;
	}

	maximum = movelist.size() - 1;
	std::uniform_int_distribution<int> movepick(0, std::max(0, maximum));
	int move_roll = movepick(rng);
	auto newloc = movelist.at(move_roll).second;
	auto currentloc = movelist.at(move_roll).first;
	auto piece = brd.blackPieces.find({currentloc.x,currentloc.y });

	if (piece != brd.blackPieces.end())
	{
		piece->second->MoveTo(newloc);
		//Set the new position
		
		//Check if we're moving our king, if so then update the king's position
		kingInstance = dynamic_cast<King*>(piece->second.get());
		if (kingInstance != nullptr)
		{
			brd.UpdateBlackKingLoc({ newloc.x,newloc.y });
		}
		//Reinsert into the map at the new position, remove the old entry
		brd.blackPieces.insert_or_assign({ newloc.x, newloc.y }, std::move(piece->second));
		brd.blackPieces.erase({ currentloc.x,currentloc.y });	
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
