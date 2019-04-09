#include "Player.h"

Player::Player(Window & wnd, Board & brd, GUI& gui)
	:
	Actor(wnd,brd),
	gui(gui)
{
}

void Player::DoTurn()
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
			auto piece = brd.whitePieces.find({ selectedPiece.x,selectedPiece.y });
			if (piece != brd.whitePieces.end())
			{
				if (TestForCheckMate())
				{
					return;
				}
				TestForStaleMate();
				//If the piece exists then store it and get the moves for it - different moves depending on whether we are checked or not
				pieceSelected = true;

				//Check if we've clicked the King
				kingInstance = dynamic_cast<King*>(brd.whitePieces.find({ selectedPiece.x, selectedPiece.y })->second.get());

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
			auto it = (std::find_if(selectedMoves.begin(), selectedMoves.end(), [&](const std::pair<Coords, Coords>& rhs) {
			return selectedTarget == rhs.second;}));

			auto piece = brd.whitePieces.find({ selectedPiece.x,selectedPiece.y });
			if (piece != brd.whitePieces.end() && it != selectedMoves.end() )
			{
				//Insert at new position and delete old one
				piece->second.get()->MoveTo({ selectedTarget.x, selectedTarget.y });
				brd.whitePieces.insert_or_assign({ selectedTarget.x, selectedTarget.y }, std::move(piece->second));
				brd.whitePieces.erase({ selectedPiece.x,selectedPiece.y });
				
				//Update the king position if we've moved it - if we're castling we also need to move the relevent rook
				if (kingInstance)
				{
					brd.UpdateWhiteKingLoc({ selectedTarget.x,selectedTarget.y });
					//Left castling
					if (selectedTarget.x == 2 && !hasCastled)
					{
						auto rook = brd.whitePieces.find({ 0,7 });
						if (rook != brd.whitePieces.end())
						{
							rook->second.get()->MoveTo({ 3, 7 });
							brd.whitePieces.insert_or_assign({ 3, 7 }, std::move(rook->second));
							brd.whitePieces.erase({ 0,7 });
							brd.SetLeftCastling(false);
							brd.SetRightCastling(false);
							hasCastled = true;
						}
					}
					//right castling
					if (selectedTarget.x == 6 && !hasCastled)
					{
						auto rook = brd.whitePieces.find({ 7,7 });
						if (rook != brd.whitePieces.end())
						{
							rook->second.get()->MoveTo({ 5, 7 });
							brd.whitePieces.insert_or_assign({ 5, 7 }, std::move(rook->second));
							brd.whitePieces.erase({ 7,7 });
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
				pawnInstance = dynamic_cast<Pawn*>(brd.whitePieces.find({ selectedTarget.x, selectedTarget.y })->second.get());
				if (pawnInstance != nullptr && selectedPiece.y == 1 && selectedTarget.y == 0)
				{
					promotion = true;
				}

				//Enpassant - we're a pawn moving from initial position to 2 spaces up
				if (selectedPiece.y == 6 && selectedTarget.y == 4 && pawnInstance)
				{
					brd.SetWhiteEnpassant(true);
				}

				//Check for taking pieces
				if (brd.blackPieces.count({ selectedTarget.x, selectedTarget.y }) > 0)
				{
					brd.blackPieces.erase({ selectedTarget.x,selectedTarget.y });
				}
				//Enpassant take
				if (brd.GetBlackEnpassant() && brd.blackPieces.count({ selectedTarget.x, selectedTarget.y+1 }) > 0)
				{ 
					brd.blackPieces.erase({ selectedTarget.x,selectedTarget.y+1 }); 
				}
				//end of turn cleanup
				pieceSelected = false;
				playerTurn = false;
				brd.playedMoves.push_back(std::make_pair(selectedPiece, selectedTarget));
			}	
			//Get our new targets for the black players turn
			brd.whitePieceTargets.clear();
			for (const auto& p : brd.whitePieces)
			{
				p.second->GetTargets(&brd.blackPieces);
			}
			//We can only get moves that result in not being checked so we can safely assume we're not checked now
			checked = false;
			//Enpassant lasts for one turn only
			brd.SetBlackEnpassant(false);
		}	
	}
		
	//Remove any selected pieces
	if (wnd.inpt.RightMsePressed())
	{
			pieceSelected = false;
			selectedPiece = { 0,0 };
	}
}

void Player::DrawPossibleMoves(Graphics& gfx)
{
	const auto moves = brd.whitePieces.find({ selectedPiece.x, selectedPiece.y });
	if (moves != brd.whitePieces.end())
	{
		for (const auto& m : selectedMoves)
		{
			auto position = brd.TranslateCoords({ m.second });
			gfx.DrawSprite(position.first, position.second, target);
		}
	}
}

void Player::DrawPieces(Graphics & gfx) const
{
	for (const auto& x : brd.whitePieces)
	{
		auto position = brd.TranslateCoords(x.second.get());
		gfx.DrawSprite(position.first, position.second, x.second->GetSprite());
	}
}

void Player::DrawChecked(Graphics & gfx) const
{
	if (checked)
	{
		auto position = brd.TranslateCoords({ brd.GetWhiteKingLoc() });
		gfx.DrawSprite(position.first, position.second, inCheck);
	}
}

void Player::Promote(Map * map)
{
	int x = 0;
	int y = 0;

	if (wnd.inpt.LeftMsePressed())
	{
		x = wnd.inpt.GetMseX();
		y = wnd.inpt.GetMseY();
	}
	
	//Bishop
	if (x >= gui.GetPromoteGraphicX()+25 && x <= gui.GetPromoteGraphicX()+85 && y >= gui.GetPromoteGraphicY()+75 && y <= gui.GetPromoteGraphicY()+130)
	{
		map->insert_or_assign({ pawnInstance->GetCoords().x, pawnInstance->GetCoords().y }, std::make_shared<Bishop>(pawnInstance->GetCoords().x, 0, "./Sprites/bishopW.bmp", true, brd));
		promotion = false;
		playerTurn = false;
	}
	//Knight
	if (x >= gui.GetPromoteGraphicX() + 155 && x <= gui.GetPromoteGraphicX() + 215 && y >= gui.GetPromoteGraphicY() + 75 && y <= gui.GetPromoteGraphicY() + 130)
	{
		map->insert_or_assign({ pawnInstance->GetCoords().x, pawnInstance->GetCoords().y }, std::make_shared<Knight>(pawnInstance->GetCoords().x, 0, "./Sprites/knightW.bmp", true, brd));
		promotion = false;
		playerTurn = false;
	}
	//Rook
	if (x >= gui.GetPromoteGraphicX() + 25 && x <= gui.GetPromoteGraphicX() + 85 && y >= gui.GetPromoteGraphicY() + 155 && y <= gui.GetPromoteGraphicY() + 210)
	{
		map->insert_or_assign({ pawnInstance->GetCoords().x, pawnInstance->GetCoords().y }, std::make_shared<Rook>(pawnInstance->GetCoords().x, 0, "./Sprites/rookW.bmp", true, brd));
		promotion = false;
		playerTurn = false;
	}
	//Queen
	if (x >= gui.GetPromoteGraphicX()+155 && x <= gui.GetPromoteGraphicX()+215 && y >= gui.GetPromoteGraphicY() + 155 && y <= gui.GetPromoteGraphicY() + 210)
	{
		map->insert_or_assign({ pawnInstance->GetCoords().x, pawnInstance->GetCoords().y }, std::make_shared<Queen>(pawnInstance->GetCoords().x, 0, "./Sprites/queenW.bmp", true, brd));

		promotion = false;
		playerTurn = false;
	}
}

bool Player::PlayerTurn() const
{
	return playerTurn;
}

void Player::SetPlayerTurn()
{
	playerTurn = true;
}

void Player::TestForCheck()
{
	//Go through the possible targets of the black pieces and see if we're checked.
	const auto p = std::find(brd.blackPieceTargets.begin(), brd.blackPieceTargets.end(), brd.GetWhiteKingLoc());
	if (p != brd.blackPieceTargets.end())
	{
		checked = true;
		return;
	}
	checked = false;
}

bool Player::TestForCheckMate()
{
	//If we have no possible moves and we're chcked then game over.
	if (checked)
	{
		movelist.clear();
		for (const auto& p : brd.whitePieces)
		{
			auto temp = p.second->GetMoves();
			movelist.insert(movelist.end(), temp.begin(), temp.end());
		}
		if (movelist.size() == 0)
		{
			cMated = true;
		}
		return cMated;
	}
	return cMated;
}


void Player::TestForStaleMate()
{
	for (const auto& p : brd.whitePieces)
	{
		auto temp = p.second->GetMoves();
		movelist.insert(movelist.end(), temp.begin(), temp.end());
	}
	if (movelist.size() == 0 && !checked)
	{
		stalemate = true;
	}
}

void Player::TestForCastling()
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
			if (brd.whitePieces.count({ 1, 7 }) == 0 && brd.whitePieces.count({ 2, 7 }) == 0 &&
				brd.whitePieces.count({ 3, 7 }) == 0 && brd.blackPieces.count({ 1, 7 }) == 0 && brd.blackPieces.count({ 2, 7 }) == 0 &&
				brd.blackPieces.count({ 3, 7 }) == 0 && brd.blackPieceTargets.count({ 2,7 }) == 0 && brd.blackPieceTargets.count({ 3,7 }) == 0)
			{
				brd.SetLeftCastling(true);
			}
		}

		if (rightRookMoved == brd.playedMoves.end())
		{
			//Make sure there are no pieces in the way
			if (brd.whitePieces.count({ 5, 7 }) == 0 && brd.whitePieces.count({ 6, 7 }) == 0 &&
				brd.blackPieces.count({ 5, 7 }) == 0 && brd.blackPieces.count({ 6, 7 }) == 0 &&
				brd.blackPieceTargets.count({ 5, 7 }) == 0 && brd.blackPieceTargets.count({ 6, 7 }) == 0)
			{
				brd.SetRightCastling(true);
			}
		}
	}
}
