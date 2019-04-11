#include "Opponent.h"



Opponent::Opponent(Window& wnd,Board & brd)
	:
	Actor(wnd,brd),
	promotionSprite("./Sprites/promoteB.bmp"),
	rng(rd())
{
}

void Opponent::DoTurn()
{
	//timer.Start();
	//GenerationZero();
	GenerationOne();
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

void Opponent::TestForCastling()
{
	//Castling checks - we only want to do this if we haven't castled yet
	if (kingInstance && !checked && !hasCastled)
	{
		//Check that our pieces haven't moved previously by looking at the previously played moves list.
		const auto leftRookMoved = std::find_if(brd.playedMoves.begin(), brd.playedMoves.end(), [&](const std::pair<Coords, Coords>& rhs) {
			return rhs.first == leftRookStartLoc;
		});
		const auto rightRookMoved = std::find_if(brd.playedMoves.begin(), brd.playedMoves.end(), [&](const std::pair<Coords, Coords>& rhs) {
			return rhs.first == startKingLoc;
		});

		//First we check the King and Left most rook
		if (leftRookMoved == brd.playedMoves.end())
		{
			//Make sure there are no pieces in the way and that the squares we're moving through aren't under attack
			if (brd.blackPieces.count({ 1, 0 }) == 0 && brd.blackPieces.count({ 2, 0 }) == 0 &&
				brd.blackPieces.count({ 3, 0 }) == 0 && brd.whitePieces.count({ 1, 0 }) == 0 && brd.whitePieces.count({ 2, 0 }) == 0 &&
				brd.whitePieces.count({ 3, 0 }) == 0 && brd.whitePieceTargets.count({ 2,0 }) == 0 && brd.whitePieceTargets.count({ 3,0 }) == 0)
			{
				brd.SetLeftCastling(true);
			}
		}

		if (rightRookMoved == brd.playedMoves.end())
		{
			//Make sure there are no pieces in the way
			if (brd.blackPieces.count({ 5, 0 }) == 0 && brd.blackPieces.count({ 6, 0 }) == 0 &&
				brd.whitePieces.count({ 5, 0 }) == 0 && brd.whitePieces.count({ 6, 0 }) == 0 &&
				brd.whitePieceTargets.count({ 5, 0 }) == 0 && brd.whitePieceTargets.count({ 6, 0 }) == 0)
			{
				brd.SetRightCastling(true);
			}
		}
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
		TestForCastling();

		if (kingInstance)
		{
			brd.UpdateBlackKingLoc({ newloc.x,newloc.y });

			//Left castling
			if (newloc.x == 2 && !hasCastled)
			{
				auto rook = brd.blackPieces.find({ 0,0 });
				if (rook != brd.blackPieces.end())
				{
					rook->second.get()->MoveTo({ 3, 0 });
					brd.blackPieces.insert_or_assign({ 3, 0 }, std::move(rook->second));
					brd.blackPieces.erase(std::make_pair( 0,0));
					brd.SetLeftCastling(false);
					brd.SetRightCastling(false);
					hasCastled = true;
				}
			}
			//right castling
			if (newloc.x == 6 && !hasCastled)
			{
				auto rook = brd.blackPieces.find({ 7,0 });
				if (rook != brd.blackPieces.end())
				{
					rook->second.get()->MoveTo({ 5, 0 });
					brd.blackPieces.insert_or_assign({ 5, 0 }, std::move(rook->second));
					brd.blackPieces.erase({ 7,0 });
					brd.SetLeftCastling(false);
					brd.SetRightCastling(false);
					hasCastled = true;
				}
			}
			//If the King moves but doesn't castle then they cannot again
			brd.SetLeftCastling(false);
			brd.SetRightCastling(false);
			hasCastled = true;

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
	if (brd.GetWhiteEnpassant() && brd.whitePieces.count({ newloc.x, newloc.y - 1 }) > 0)
	{
		brd.whitePieces.erase({ newloc.x,newloc.y - 1 });
	}

	//Enpassant - we're a pawn moving from initial position to 2 spaces up
	if (currentloc.y == 1 && newloc.y == 3 && pawnInstance)
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
	
	//Save our state before MiniMax
	initialState = brd.blackPieces;
	whiteInitialState = brd.whitePieces;
	initialBlackPieceTargets = brd.blackPieceTargets;
	initialWhitePieceTargets = brd.whitePieceTargets;
	initialBlackKingLoc = brd.GetBlackKingLoc();
	initialWhiteKingLoc = brd.GetWhiteKingLoc();

	auto move = Minimax(movelist);

	//Assign the current position and new position to variables
	auto newloc = move.second;
	auto currentloc = move.first;
	//find the piece in the map based on the current position
	auto piece = brd.blackPieces.find({ currentloc.x,currentloc.y });

	//As long as we found the piece
	if (piece != brd.blackPieces.end())
	{
		piece->second->MoveTo(newloc);
		//Set the new position

		//Check if we're moving our king, if so then update the king's position
		kingInstance = dynamic_cast<King*>(piece->second.get());
		TestForCastling();

		if (kingInstance)
		{
			brd.UpdateBlackKingLoc({ newloc.x,newloc.y });

			//Left castling
			if (newloc.x == 2 && !hasCastled)
			{
				auto rook = brd.blackPieces.find({ 0,0 });
				if (rook != brd.blackPieces.end())
				{
					rook->second.get()->MoveTo({ 3, 0 });
					brd.blackPieces.insert_or_assign({ 3, 0 }, std::move(rook->second));
					brd.blackPieces.erase(std::make_pair(0, 0));
					brd.SetLeftCastling(false);
					brd.SetRightCastling(false);
					hasCastled = true;
				}
			}
			//right castling
			if (newloc.x == 6 && !hasCastled)
			{
				auto rook = brd.blackPieces.find({ 7,0 });
				if (rook != brd.blackPieces.end())
				{
					rook->second.get()->MoveTo({ 5, 0 });
					brd.blackPieces.insert_or_assign({ 5, 0 }, std::move(rook->second));
					brd.blackPieces.erase({ 7,0 });
					brd.SetLeftCastling(false);
					brd.SetRightCastling(false);
					hasCastled = true;
				}
			}
			//If the King moves but doesn't castle then they cannot again
			brd.SetLeftCastling(false);
			brd.SetRightCastling(false);
			hasCastled = true;

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
	if (brd.GetWhiteEnpassant() && brd.whitePieces.count({ newloc.x, newloc.y - 1 }) > 0)
	{
		brd.whitePieces.erase({ newloc.x,newloc.y - 1 });
	}

	//Enpassant - we're a pawn moving from initial position to 2 spaces up
	if (currentloc.y == 1 && newloc.y == 3 && pawnInstance)
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

void Opponent::TestMove(std::pair<Coords, Coords> move)
{
	//Assign the current position and new position to variables
	auto newloc = move.second;
	auto currentloc = move.first;
	//find the piece in the map based on the current position
	auto piece = initialState.find({ currentloc.x,currentloc.y });

	//As long as we found the piece
	if (piece != initialState.end())
	{
	
		//Check if we're moving our king, if so then update the king's position
		kingInstance = dynamic_cast<King*>(piece->second.get());
		//TestForCastling();

		if (kingInstance)
		{
			initialBlackKingLoc = newloc;

		}
		//If we take a piece then update that too
		if (whiteInitialState.count({ newloc.x, newloc.y }) > 0)
		{
			whiteInitialState.erase({ newloc.x,newloc.y });
		}
		//Enpassant capture
		if (brd.GetWhiteEnpassant() && whiteInitialState.count({ newloc.x, newloc.y - 1 }) > 0)
		{
			whiteInitialState.erase({ newloc.x,newloc.y - 1 });
		}

		//Enpassant - we're a pawn moving from initial position to 2 spaces up
		if (currentloc.y == 1 && newloc.y == 3 && pawnInstance != nullptr)
		{
			brd.SetBlackEnpassant(true);
		}

		//Reinsert into the map at the new position, remove the old entry
		initialState.insert_or_assign({ newloc.x, newloc.y }, piece->second);
		initialState.erase({ currentloc.x,currentloc.y });

		//recalculate our targets following our turn
		initialBlackPieceTargets.clear();
		for (const auto& p : initialState)
		{
			p.second->GetTargets(&whiteInitialState);
		}

		//We can only get moves that result in not being checked so we can safely assume we're not checked now
		checked = false;
	}
}

void Opponent::UndoTestMove()
{

	for (const auto& p : brd.whitePieces)
	{
		p.second->MoveTo({ p.first.first,p.first.second });
	}
	for (const auto& p : brd.blackPieces)
	{
		p.second->MoveTo({ p.first.first,p.first.second });
	}
	initialState = brd.blackPieces;
	whiteInitialState = brd.whitePieces;
	initialWhitePieceTargets = brd.whitePieceTargets;
	initialBlackPieceTargets = brd.blackPieceTargets;
	initialWhiteKingLoc = brd.GetWhiteKingLoc();
	initialBlackKingLoc = brd.GetBlackKingLoc();

	
	
}

int Opponent::TestMoveScore() const
{
	int score = 0;
	for (const auto& p : brd.blackPieces)
	{
		score += p.second->GetScore();
	}
	for (const auto& p : brd.whitePieces)
	{
		score -= p.second->GetScore();
	}
	return score;
}

std::pair<Coords, Coords> Opponent::Minimax(std::vector < std::pair<Coords, Coords>> moves_in)
{
	//for evaluating score
	int value = 0;
	int bestMoveValue = -99999;
	int bestMoveValueNeg = 99999;
	std::vector<std::pair<Coords, Coords>> whiteMoves;
	std::vector<std::pair<Coords, Coords>> temp;
	std::set<std::pair<Coords, Coords>> bestMoves;
	//for every move in the input moves list
	//We want to do that move
	//Get the score and save the value of it
	//We then want to go through the white piece moves based off of that move
	//for each one we want to do each move
	//Get the score and subtract it from the above score
	//If it is greater than the current total (starting at -99999) then we want to save the move
	//We then reset the white pieces and continue til the loop ends
	//We then reset the black pieces and continue to the loop ends
	//We then reset the all maps and targets and return the best move
	bestMoves.clear();
	for (const auto m : moves_in)
	{
		TestMove(m);
		whiteMoves.clear();
		for (const auto p : whiteInitialState)
		{
			temp = p.second->GetMoves();
			whiteMoves.insert(whiteMoves.end(), temp.begin(), temp.end());
		}

		for (const auto k : whiteMoves)
		{
			value = 0;
			//do white move
			DoWhiteMove(k);
			//Test the game board value
			value = TestMoveScore();

			//The higher the value, the better the move for black
			if (value < bestMoveValueNeg)
			{
				if (value > bestMoveValue)
				{
					bestMoveValue = value;
					bestMove = m;
				}
				bestMoveValueNeg = value;
			}
			
			else if (value == bestMoveValue)
			{
				bestMoves.insert(m);
			}

			//Undo any moves
			ResetWhiteMove();

		}
		//Undo everything
		UndoTestMove();
	}
			
	//Undo everything
	UndoTestMove();

	if (bestMoves.size() > 0)
	{
		int maximum = movelist.size() - 1;
		std::uniform_int_distribution<int> movepick(0, std::max(0, maximum));
		int move_roll = movepick(rng);
		std::set<std::pair<Coords,Coords>>::const_iterator it(bestMoves.begin());
		advance(it, move_roll);
		bestMove = *it;
	}
	
	return bestMove;
}

void Opponent::ResetWhiteMove()
{
	for (const auto& p : brd.whitePieces)
	{
		p.second->MoveTo({ p.first.first,p.first.second });
	}
	initialWhitePieceTargets = brd.whitePieceTargets;
	whiteInitialState = brd.whitePieces;
	initialWhiteKingLoc = brd.GetWhiteKingLoc();
}

void Opponent::DoWhiteMove(const std::pair<Coords, Coords> input)
{
	auto piece = whiteInitialState.find({ input.first.x,input.first.y });
	if (piece != whiteInitialState.end())
	{
		piece->second.get()->MoveTo({ input.second.x, input.second.y });
		whiteInitialState.insert_or_assign({ input.second.x,input.second.y }, piece->second);
		whiteInitialState.erase({ input.first.x,input.first.y });
		kingInstance = dynamic_cast<King*>(piece->second.get());
		//Update the king position if we've moved it - if we're castling we also need to move the relevent rook
		if (kingInstance)
		{
			initialWhiteKingLoc = input.second;
		}
			//Enpassant - we're a pawn moving from initial position to 2 spaces up
			if (input.first.y == 6 && input.second.y == 4 && pawnInstance)
			{
				brd.SetWhiteEnpassant(true);
			}

			//Check for taking pieces
			if (initialState.count({ input.second.x, input.second.y }) > 0)
			{
				initialState.erase({ input.second.x, input.second.y });
			}
			//Enpassant take
			if (brd.GetBlackEnpassant() && initialState.count({ input.second.x, input.second.y + 1 }) > 0)
			{
				initialState.erase({ input.second.x, input.second.y + 1 });
			}

			//Get our new targets for the black players turn
			initialWhitePieceTargets.clear();
			for (const auto& p : whiteInitialState)
			{
				p.second->GetTargets(&initialState);
			}
			//We can only get moves that result in not being checked so we can safely assume we're not checked now
			checked = false;
	}
}
