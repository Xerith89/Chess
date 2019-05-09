#include "BlackPlayer.h"



BlackPlayer::BlackPlayer(Window& wnd,Board & brd)
	:
	Actor(wnd,brd),
	promotionSprite("./Sprites/promoteB.bmp"),
	rng(rd())
{
}

void BlackPlayer::DoTurn()
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

void BlackPlayer::DrawPieces(Graphics & gfx) const
{
	for (const auto& x : brd.blackPieces)
	{
		auto position = brd.TranslateCoords(x.second.get());
		gfx.DrawSprite(position.first, position.second, x.second->GetSprite());
	}
}

void BlackPlayer::DrawChecked(Graphics & gfx) const
{
	if (checked)
	{
		auto position = brd.TranslateCoords({ brd.GetBlackKingLoc() });
		gfx.DrawSprite(position.first, position.second, inCheck);
	}
}

void BlackPlayer::Promote(Map * map)
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

void BlackPlayer::TestForCheck()
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

void BlackPlayer::mDoTurn()
{
	//Check for left mouse button
	if (wnd.inpt.LeftMsePressed())
	{
		//Check for an unselected piece or a piece with no available moves - we can then select a new piece
		if (!pieceSelected)
		{
			//new move so clear out our move buffer
			selectedMoves.clear();

			//Translate the mouse position to board coords
			selectedPiece = brd.TranslateCoords(wnd.inpt.GetMseX(), wnd.inpt.GetMseY());
			auto piece = brd.blackPieces.find({ selectedPiece.x,selectedPiece.y });
			if (piece != brd.blackPieces.end())
			{
				if (TestForCheckMate())
				{
					return;
				}
				TestForStaleMate();
				//If the piece exists then store it and get the moves for it - different moves depending on whether we are checked or not
				pieceSelected = true;

				//Check if we've clicked the King
				kingInstance = dynamic_cast<King*>(brd.blackPieces.find({ selectedPiece.x, selectedPiece.y })->second.get());

				TestForCastling();

				selectedMoves = piece->second->GetMoves();

				//We didn't click something with valid moves
				if (selectedMoves.empty())
				{
					pieceSelected = false;
					return;
				}
			}
		}
		else
		{
			//We already have a target so we're clicking on a new position - do the usual translate
			selectedTarget = brd.TranslateCoords(wnd.inpt.GetMseX(), wnd.inpt.GetMseY());
			auto it = (std::find_if(selectedMoves.begin(), selectedMoves.end(), [&](const std::pair<Coords, Coords> & rhs) {
				return selectedTarget == rhs.second; }));

			auto piece = brd.blackPieces.find({ selectedPiece.x,selectedPiece.y });
			if (piece != brd.blackPieces.end() && it != selectedMoves.end())
			{
				//Insert at new position and delete old one
				piece->second.get()->MoveTo({ selectedTarget.x, selectedTarget.y });
				brd.blackPieces.insert_or_assign({ selectedTarget.x, selectedTarget.y }, std::move(piece->second));
				brd.blackPieces.erase({ selectedPiece.x,selectedPiece.y });

				//Update the king position if we've moved it - if we're castling we also need to move the relevent rook
				if (kingInstance)
				{
					brd.UpdateBlackKingLoc({ selectedTarget.x,selectedTarget.y });
					//Left castling
					if (selectedTarget.x == 1 && !hasCastled)
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
					if (selectedTarget.x == 5 && !hasCastled)
					{
						auto rook = brd.blackPieces.find({ 7,0 });
						if (rook != brd.blackPieces.end())
						{
							rook->second.get()->MoveTo({ 4, 0 });
							brd.blackPieces.insert_or_assign({ 4, 0 }, std::move(rook->second));
							brd.blackPieces.erase({ 7,0 });
							brd.SetLeftCastling(false);
							brd.SetRightCastling(false);
							hasCastled = true;
						}
					}
					brd.SetLeftCastling(false);
					brd.SetRightCastling(false);
					hasCastled = true;
				}

				//Check if we're moving a pawn so we can check for promotion
				pawnInstance = dynamic_cast<Pawn*>(brd.blackPieces.find({ selectedTarget.x, selectedTarget.y })->second.get());
				if (pawnInstance != nullptr && selectedPiece.y == 6 && selectedTarget.y == 7)
				{
					promotion = true;
				}

				//Enpassant - we're a pawn moving from initial position to 2 spaces up
				if (selectedPiece.y == 1 && selectedTarget.y == 3 && pawnInstance)
				{
					brd.SetBlackEnpassant(true);
				}

				//Check for taking pieces
				if (brd.whitePieces.count({ selectedTarget.x, selectedTarget.y }) > 0)
				{
					brd.whitePieces.erase({ selectedTarget.x,selectedTarget.y });
				}
				//Enpassant take
				if (brd.GetWhiteEnpassant() && brd.whitePieces.count({ selectedTarget.x, selectedTarget.y + 1 }) > 0)
				{
					brd.whitePieces.erase({ selectedTarget.x,selectedTarget.y + 1 });
				}
				//end of turn cleanup
				pieceSelected = false;
				playerTurn = false;
				packetReady = true;
				brd.playedMoves.push_back(std::make_pair(selectedPiece, selectedTarget));
			}
			//Get our new targets for the black players turn
			brd.blackPieceTargets.clear();
			for (const auto& p : brd.blackPieces)
			{
				p.second->GetTargets(&brd.whitePieces);
			}
			//We can only get moves that result in not being checked so we can safely assume we're not checked now
			checked = false;
			//Enpassant lasts for one turn only
			brd.SetWhiteEnpassant(false);
		}

	}

	//Remove any selected pieces
	if (wnd.inpt.RightMsePressed())
	{
		pieceSelected = false;
		selectedPiece = { 7,7 };
	}
}

bool BlackPlayer::PacketReady() const
{
	return packetReady;
}

void BlackPlayer::SetPacketNotReady()
{
	packetReady = false;
}

bool BlackPlayer::PlayerTurn() const
{
	return playerTurn;
}

void BlackPlayer::SetPlayerTurn(bool myTurn)
{
	playerTurn = myTurn;
}

void BlackPlayer::DoMPlayUpdate(std::pair<Coords, Coords> input)
{
	//Translate the mouse position to board coords
	selectedPiece = input.first;
	auto piece = brd.blackPieces.find({ selectedPiece.x,selectedPiece.y });
	if (piece != brd.blackPieces.end())
	{
		if (TestForCheckMate())
		{
			return;
		}
		TestForStaleMate();
		//If the piece exists then store it and get the moves for it - different moves depending on whether we are checked or not
		pieceSelected = true;

		//Check if we've clicked the King
		kingInstance = dynamic_cast<King*>(brd.blackPieces.find({ selectedPiece.x, selectedPiece.y })->second.get());

		TestForCastling();

		selectedMoves = piece->second->GetMoves();

		//We didn't click something with valid moves
		if (selectedMoves.empty())
		{
			pieceSelected = false;
			return;
		}
	
		//We already have a target so we're clicking on a new position - do the usual translate
		selectedTarget = input.second;
		auto it = (std::find_if(selectedMoves.begin(), selectedMoves.end(), [&](const std::pair<Coords, Coords> & rhs) {
			return selectedTarget == rhs.second; }));

		auto piece = brd.blackPieces.find({ selectedPiece.x,selectedPiece.y });
		if (piece != brd.blackPieces.end() && it != selectedMoves.end())
		{
			//Insert at new position and delete old one
			piece->second.get()->MoveTo({ selectedTarget.x, selectedTarget.y });
			brd.blackPieces.insert_or_assign({ selectedTarget.x, selectedTarget.y }, std::move(piece->second));
			brd.blackPieces.erase({ selectedPiece.x,selectedPiece.y });

			//Update the king position if we've moved it - if we're castling we also need to move the relevent rook
			if (kingInstance)
			{
				brd.UpdateBlackKingLoc({ selectedTarget.x,selectedTarget.y });
				//Left castling
				if (selectedTarget.x == 1 && !hasCastled)
				{
					auto rook = brd.blackPieces.find({ 0,0 });
					if (rook != brd.blackPieces.end())
					{
						rook->second.get()->MoveTo({ 2, 0 });
						brd.blackPieces.insert_or_assign({ 2, 0 }, std::move(rook->second));
						brd.blackPieces.erase(std::make_pair(0, 0));
						brd.SetLeftCastling(false);
						brd.SetRightCastling(false);
						hasCastled = true;
					}
				}
				//right castling
				if (selectedTarget.x == 5 && !hasCastled)
				{
					auto rook = brd.blackPieces.find({ 7,0 });
					if (rook != brd.blackPieces.end())
					{
						rook->second.get()->MoveTo({ 4, 0 });
						brd.blackPieces.insert_or_assign({ 4, 0 }, std::move(rook->second));
						brd.blackPieces.erase({ 7,0 });
						brd.SetLeftCastling(false);
						brd.SetRightCastling(false);
						hasCastled = true;
					}
				}
				brd.SetLeftCastling(false);
				brd.SetRightCastling(false);
				hasCastled = true;
			}

			//Check if we're moving a pawn so we can check for promotion
			pawnInstance = dynamic_cast<Pawn*>(brd.blackPieces.find({ selectedTarget.x, selectedTarget.y })->second.get());
			if (pawnInstance != nullptr && selectedPiece.y == 6 && selectedTarget.y == 7)
			{
				promotion = true;
			}

			//Enpassant - we're a pawn moving from initial position to 2 spaces up
			if (selectedPiece.y == 1 && selectedTarget.y == 3 && pawnInstance)
			{
				brd.SetBlackEnpassant(true);
			}

			//Check for taking pieces
			if (brd.whitePieces.count({ selectedTarget.x, selectedTarget.y }) > 0)
			{
				brd.whitePieces.erase({ selectedTarget.x,selectedTarget.y });
			}
			//Enpassant take
			if (brd.GetWhiteEnpassant() && brd.whitePieces.count({ selectedTarget.x, selectedTarget.y + 1 }) > 0)
			{
				brd.whitePieces.erase({ selectedTarget.x,selectedTarget.y + 1 });
			}
			//end of turn cleanup
			pieceSelected = false;
			playerTurn = false;
			packetReady = true;
			brd.playedMoves.push_back(std::make_pair(selectedPiece, selectedTarget));
		}
		//Get our new targets for the black players turn
		brd.blackPieceTargets.clear();
		for (const auto& p : brd.blackPieces)
		{
			p.second->GetTargets(&brd.whitePieces);
		}
		//We can only get moves that result in not being checked so we can safely assume we're not checked now
		checked = false;
		//Enpassant lasts for one turn only
		brd.SetWhiteEnpassant(false);
		}
}

void BlackPlayer::DrawPossibleMoves(Graphics& gfx)
{
	const auto moves = brd.blackPieces.find({ selectedPiece.x, selectedPiece.y });
	if (moves != brd.blackPieces.end())
	{
		for (const auto& m : selectedMoves)
		{
			auto position = brd.TranslateCoords({ m.second });
			gfx.DrawSprite(position.first, position.second, target);
		}
	}
}

bool BlackPlayer::TestForCheckMate()
{
	if (movelist.size() == 0 && checked)
	{
		cMated = true;
		return cMated;
	}
	return cMated;
}

bool BlackPlayer::TestForDraw()
{

	if (brd.blackPieces.size() == 1 && brd.whitePieces.size() == 1)
	{
		//Only kings left so we have a draw
		return true;
	}

	if (brd.blackPieces.size() == 2 && brd.whitePieces.size() == 1)
	{
		//we've got two pieces left - check what they are
		for (const auto& p : brd.blackPieces)
		{
			bishopInstance = dynamic_cast<Bishop*>(p.second.get());
			knightInstance = dynamic_cast<Knight*>(p.second.get());
		}

		if (bishopInstance != nullptr || knightInstance != nullptr)
		{
			return true;
		}
	}

	if (brd.whitePieces.size() == 2 && brd.blackPieces.size() == 2)
	{
		//Test the pieces left
		for (const auto& p : brd.whitePieces)
		{
			oppoBishopInstance = dynamic_cast<Bishop*>(p.second.get());
		}

		for (const auto& p : brd.blackPieces)
		{
			bishopInstance = dynamic_cast<Bishop*>(p.second.get());
		}

		if (bishopInstance != nullptr && oppoBishopInstance != nullptr)
		{
			//If they are the on the same coloured square then we have a draw
			if (bishopInstance->GetBlackSquare() && oppoBishopInstance->GetBlackSquare())
			{
				return true;
			}
			else if (!bishopInstance->GetBlackSquare() && !oppoBishopInstance->GetBlackSquare())
			{
				return true;
			}
		}
	}
	return false;
}


void BlackPlayer::TestForStaleMate()
{
	if (movelist.size() == 0 && !checked)
	{
		stalemate = true;
	}
}

void BlackPlayer::TestForCastling()
{
	//Castling checks - we only want to do this if we haven't castled yet
	if (kingInstance && !checked && !hasCastled)
	{
		//Check that our pieces haven't moved previously by looking at the previously played moves list.
		const auto leftRookMoved = std::find_if(brd.playedMoves.begin(), brd.playedMoves.end(), [&](const std::pair<Coords, Coords>& rhs) {
			return rhs.first == leftRookStartLoc;
		});
		const auto rightRookMoved = std::find_if(brd.playedMoves.begin(), brd.playedMoves.end(), [&](const std::pair<Coords, Coords>& rhs) {
			return rhs.first == rightRookStartLoc;
		});

		//First we check the King and Left most rook
		if (leftRookMoved == brd.playedMoves.end())
		{
			//Make sure there are no pieces in the way and that the squares we're moving through aren't under attack
			if (brd.blackPieces.count({ 1, 0 }) == 0 && brd.blackPieces.count({ 2, 0 }) == 0 &&
				brd.whitePieces.count({ 1, 0 }) == 0 && brd.whitePieces.count({ 2, 0 }) == 0 &&
				brd.whitePieces.count({ 3, 0 }) == 0 && brd.whitePieceTargets.count({ 2,0 }) == 0)
			{
				brd.SetLeftCastling(true);
			}
		}

		if (rightRookMoved == brd.playedMoves.end())
		{
			//Make sure there are no pieces in the way
			if (brd.blackPieces.count({ 5, 0 }) == 0 && brd.blackPieces.count({ 6, 0 }) == 0 && brd.blackPieces.count({ 4, 0 }) == 0 &&
				brd.whitePieces.count({ 5, 0 }) == 0 && brd.whitePieces.count({ 6, 0 }) == 0 &&
				brd.whitePieceTargets.count({ 4, 0 }) == 0 && brd.whitePieceTargets.count({ 5, 0 }) == 0 && brd.whitePieceTargets.count({ 6, 0 }) == 0)
			{
				brd.SetRightCastling(true);
			}
		}
	}
}

//Our first AI that will be random based
void BlackPlayer::GenerationZero()
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
					rook->second.get()->MoveTo({ 4, 0 });
					brd.blackPieces.insert_or_assign({ 4, 0 }, std::move(rook->second));
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

void BlackPlayer::GenerationOne()
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
					rook->second.get()->MoveTo({ 2, 0 });
					brd.blackPieces.insert_or_assign({ 2, 0 }, std::move(rook->second));
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

void BlackPlayer::GenerationTwo()
{
	//MiniMax with depth of 5
}

void BlackPlayer::GenerationThree()
{
	//Introduce alphabeta to G2
}

void BlackPlayer::GenerationFour()
{
	//Introduce nullMove
}

void BlackPlayer::GenerationFive()
{
	//parallel MiniMax 
}

void BlackPlayer::GenerationSix()
{
	//12 moves ahead
}

void BlackPlayer::TestMove(std::pair<Coords, Coords> move)
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

void BlackPlayer::UndoTestMove()
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

int BlackPlayer::TestMoveScore() const
{
	int score = 0;
	for (const auto& p : initialState)
	{
		score += p.second->GetScore();
	}
	for (const auto& p : whiteInitialState)
	{
		score -= p.second->GetScore();
	}
	return score;
}

std::pair<Coords, Coords> BlackPlayer::Minimax(std::vector < std::pair<Coords, Coords>> moves_in)
{
	//for evaluating score
	int value = 0;
	int bestMoveValue = -99999;
	std::vector<std::pair<Coords, Coords>> whiteMoves;
	std::vector<std::pair<Coords, Coords>> temp;
	std::set<std::pair<Coords, Coords>> bestMoves;
	//for every move in the input moves list
	//We want to do that move
	//We then want to go through the white piece moves based off of that move
	//for each one we want to do each move
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
			//do white move
			DoWhiteMove(k);
			//Test the game board value
			value = TestMoveScore();

			//The higher the value, the better the move for black
			if (value > bestMoveValue)
			{
				bestMoveValue = value;
				bestMove = m;
				bestMoves.clear();
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
		int maximum = bestMoves.size() - 1;
		std::uniform_int_distribution<int> movepick(0, std::max(0, maximum));
		int move_roll = movepick(rng);
		std::set<std::pair<Coords,Coords>>::const_iterator it(bestMoves.begin());
		advance(it, move_roll);
		bestMove = *it;
	}
	
	return bestMove;
}

void BlackPlayer::ResetWhiteMove()
{
	initialWhitePieceTargets = brd.whitePieceTargets;
	whiteInitialState = brd.whitePieces;
	initialWhiteKingLoc = brd.GetWhiteKingLoc();
}

void BlackPlayer::DoWhiteMove(const std::pair<Coords, Coords> input)
{
	auto piece = whiteInitialState.find({ input.first.x,input.first.y });
	if (piece != whiteInitialState.end())
	{
		kingInstance = dynamic_cast<King*>(piece->second.get());
		piece->second.get()->MoveTo({ input.second.x, input.second.y });
		whiteInitialState.insert_or_assign({ input.second.x,input.second.y }, piece->second);
		whiteInitialState.erase({ input.first.x,input.first.y });
		
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
