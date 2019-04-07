#include "Opponent.h"



Opponent::Opponent(Window& wnd,Board & brd)
	:
	Actor(wnd,brd),
	promotionSprite("./Sprites/promoteB.bmp")
{
}

void Opponent::DoTurn()
{
	//timer.Start();
	GenerationZero();
	//GenerationOne();
	//GenerationTwo();
	//GenerationThree();
	//GenerationFour();
	//GenerationFive();
	//GenerationSix();
	//std::string time("AI executed in : " + std::to_string(timer.Mark()) + " milliseconds.");
	//MessageBox(wnd.GetHandle(), time.c_str(), "Speed", MB_OK);
}

void Opponent::DrawPieces(Graphics & gfx) const
{
	for (const auto& x : brd.blackPieces)
	{
		auto position = brd.TranslateCoords(x.second.get());
		gfx.DrawSprite(position.first, position.second, x.second->GetSprite());
	}
}

void Opponent::DrawChecked(Graphics & gfx) const
{
	if (checked)
	{
		auto position = brd.TranslateCoords({ brd.GetBlackKingLoc() });
		gfx.DrawSprite(position.first, position.second, inCheck);
	}
}

void Opponent::Promote(Map * map)
{
	std::uniform_int_distribution<int> promotedPiece(0, std::max(0,3));
	int piece = promotedPiece(rng);
	//Bishop
	switch (piece)
	{
	case 0:
		map->insert_or_assign({ pawnInstance->GetCoords().x, pawnInstance->GetCoords().y }, std::make_shared<Bishop>(pawnInstance->GetCoords().x, 7, "./Sprites/bishopB.bmp", false, brd));
		promotion = false;
		break;
	case 1:
		map->insert_or_assign({ pawnInstance->GetCoords().x, pawnInstance->GetCoords().y }, std::make_shared<Knight>(pawnInstance->GetCoords().x, 7, "./Sprites/knightB.bmp", false, brd));
		promotion = false;
		break;
	case 2:
		map->insert_or_assign({ pawnInstance->GetCoords().x, pawnInstance->GetCoords().y }, std::make_shared<Queen>(pawnInstance->GetCoords().x, 7, "./Sprites/queenB.bmp", false, brd));
		promotion = false;
		break;
	case 3:
		map->insert_or_assign({ pawnInstance->GetCoords().x, pawnInstance->GetCoords().y }, std::make_shared<Rook>(pawnInstance->GetCoords().x, 7, "./Sprites/rookB.bmp", false, brd));
		promotion = false;
		break;
	}
}

void Opponent::TestForCheck()
{
	//Go through the possible targets of the white pieces and see if we're checked.
	const auto p = std::find(brd.whitePieceTargets.begin(), brd.whitePieceTargets.end(), brd.GetBlackKingLoc());
	if (p != brd.whitePieceTargets.end())
	{
		checked = true;
		return;
	}
	checked = false;
}

bool Opponent::TestForCheckMate()
{
	if (movelist.size() == 0 && checked)
	{
		cMated = true;
		return cMated;
	}
	return cMated;
}


void Opponent::TestForStaleMate()
{
	if (movelist.size() == 0 && !checked)
	{
		stalemate = true;
	}
}

//Our first AI that will be random based
void Opponent::GenerationZero()
{
	int maximum = 0;
	movelist.clear();
	std::vector<std::pair<Coords, Coords>> temp;

	//Go through all our pieces, get moves for them. The returning vector is then amalgamated.
	for (const auto& p : brd.blackPieces)
	{
		
		temp = p.second->GetMoves();
		 movelist.insert(movelist.end(), temp.begin(), temp.end()); 
	}
	//If we have no moves and we're checked then its game over.
	if (TestForCheckMate())
	{
		return;
	}
	TestForStaleMate();
	//Make sure we index in bounds by picking a value between 0 and size of the vector -1
	maximum = movelist.size() - 1;
	std::uniform_int_distribution<int> movepick(0, std::max(0, maximum));
	int move_roll = movepick(rng);
	//Assign the current position and new position to variables
	auto newloc = movelist.at(move_roll).second;
	auto currentloc = movelist.at(move_roll).first;
	//find the piece in the map based on the current position
	auto piece = brd.blackPieces.find({currentloc.x,currentloc.y });

	//As long as we found the piece
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
		//Check if pawn for promotion
		pawnInstance = dynamic_cast<Pawn*>(piece->second.get());
		if (pawnInstance != nullptr && currentloc.y == 6 && newloc.y == 7)
		{
			promotion = true;
		}

		//Reinsert into the map at the new position, remove the old entry
		brd.blackPieces.insert_or_assign({ newloc.x, newloc.y }, std::move(piece->second));
		brd.blackPieces.erase({ currentloc.x,currentloc.y });	
	}

	//Add this move to the game played moves repository
	brd.playedMoves.push_back(std::make_pair(currentloc, newloc));
	
	//If we take a piece then update that too
	if (brd.whitePieces.count({ newloc.x, newloc.y }) > 0)
	{
		brd.whitePieces.erase({ newloc.x,newloc.y });
	}
	//Enpassant capture
	if (brd.GetWhiteEnpassant() && brd.blackPieces.count({ newloc.x, newloc.y - 1 }) > 0)
	{
		brd.whitePieces.erase({ newloc.x,newloc.y - 1 });
	}

	//Enpassant - we're a pawn moving from initial position to 2 spaces up
	if (currentloc.y == 1 && newloc.y == 3 && pawnInstance != nullptr)
	{
		brd.SetBlackEnpassant(true);
	}

	//recalculate our targets following our turn
	brd.blackPieceTargets.clear();
	for (const auto& p : brd.blackPieces)
	{
		p.second->GetTargets(&brd.whitePieces);
	}
	
	//We can only get moves that result in not being checked so we can safely assume we're not checked now
	checked = false;

	//Enpassant lasts for one turn only so we can set white enpassant to false after we move
	brd.SetWhiteEnpassant(false);
}

void Opponent::GenerationOne()
{
	//MiniMax with depth of 1
}

void Opponent::GenerationTwo()
{
	//MiniMax with depth of 5
}

void Opponent::GenerationThree()
{
	//Introduce alphabeta to G2
}

void Opponent::GenerationFour()
{
	//Introduce nullMove
}

void Opponent::GenerationFive()
{
	//parallel MiniMax 
}

void Opponent::GenerationSix()
{
	//12 moves ahead
}
