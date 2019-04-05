#include "Player.h"

Player::Player(Window & wnd, Board & brd)
	:
	Actor(wnd,brd),
	promotionSprite("./Sprites/promoteW.bmp")
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
				TestForCheck();
				if (TestForCheckMate())
				{
					return;
				}
				TestForStaleMate();
				//If the piece exists then store it and get the moves for it - different moves depending on whether we are checked or not
				pieceSelected = true;
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
				
				//Check if we're moving our king, if so then update the king's position
				kingInstance = dynamic_cast<King*>(brd.whitePieces.find({ selectedTarget.x, selectedTarget.y })->second.get());
				if (kingInstance != nullptr){brd.UpdateWhiteKingLoc({ selectedTarget.x,selectedTarget.y });}

				//Check if we're moving a pawn so we can check for promotion
				pawnInstance = dynamic_cast<Pawn*>(brd.whitePieces.find({ selectedTarget.x, selectedTarget.y })->second.get());
				if (pawnInstance != nullptr && selectedPiece.y == 1 && selectedTarget.y == 0)
				{
					promotion = true;
				}
				//Check for taking pieces
				if (brd.blackPieces.count({ selectedTarget.x, selectedTarget.y }) > 0){brd.blackPieces.erase({ selectedTarget.x,selectedTarget.y });}
						
				//end of turn cleanup
				pieceSelected = false;
				playerTurn = false;
			}	
			//Get our new targets for the black players turn
			brd.whitePieceTargets.clear();
			for (const auto& p : brd.whitePieces)
			{
				p.second->GetTargets(&brd.blackPieces);
			}
			TestForCheck();
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

void Player::DrawPromotion(Graphics & gfx) const
{
	if (promotion)
	{
		gfx.DrawSprite(200, 200, promotionSprite);
	}
}

void Player::Promote(Map * map)
{
	//Magic number use is not ideal
	int x = 0;
	int y = 0;

	if (wnd.inpt.LeftMsePressed())
	{
		x = wnd.inpt.GetMseX();
		y = wnd.inpt.GetMseY();
	}

	//Bishop
	if (x >= 225 && x <= 285 && y >= 275 && y <= 330)
	{
		map->insert_or_assign({ pawnInstance->GetCoords().x, pawnInstance->GetCoords().y }, std::make_shared<Bishop>(pawnInstance->GetCoords().x, 0, "./Sprites/bishopW.bmp", true, brd));
		promotion = false;
		playerTurn = false;
	}
	//Knight
	if (x >= 355 && x <= 415 && y >= 275 && y <= 330)
	{
		map->insert_or_assign({ pawnInstance->GetCoords().x, pawnInstance->GetCoords().y }, std::make_shared<Knight>(pawnInstance->GetCoords().x, 0, "./Sprites/knightW.bmp", true, brd));
		promotion = false;
		playerTurn = false;
	}
	//Rook
	if (x >= 225 && x <= 285 && y >= 355 && y <= 410)
	{
		map->insert_or_assign({ pawnInstance->GetCoords().x, pawnInstance->GetCoords().y }, std::make_shared<Rook>(pawnInstance->GetCoords().x, 0, "./Sprites/rookW.bmp", true, brd));
		promotion = false;
		playerTurn = false;
	}
	//Queen
	if (x >= 355 && x <= 415 && y >= 355 && y <= 410)
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

void Player::TestPawnPromotion()
{
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
