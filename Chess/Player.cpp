#include "Player.h"

Player::Player(Window & wnd, Board & brd)
	:
	wnd(wnd),
	brd(brd),
	target("./Sprites/target.bmp")
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
			//new move so clear out our move buffers
			brd.blackPieceTargets.clear();
			selectedMoves.clear();

			//call this for each black piece to get the most updated black targets
			for (const auto& p : brd.blackPieces)
			{
				p.second->GetMoves(&brd.blackPieces, &brd.whitePieces, brd.blackPieceTargets, brd.GetWhiteKingLoc(), brd.whitePieceTargets);
			}

			//Translate the mouse position to board coords
			selectedPiece = brd.TranslateCoords(wnd.inpt.GetMseX(), wnd.inpt.GetMseY());
			auto piece = brd.whitePieces.find({ selectedPiece.x,selectedPiece.y });
			if (piece != brd.whitePieces.end())
			{
				TestForCheck();
				//If the piece exists then store it and get the moves for it
				pieceSelected = true;
				selectedMoves = piece->second->GetMoves(&brd.whitePieces, &brd.blackPieces, brd.whitePieceTargets, brd.GetBlackKingLoc(),brd.blackPieceTargets);

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
			auto piece = brd.whitePieces.find({ selectedPiece.x,selectedPiece.y });
			if (piece != brd.whitePieces.end() && selectedTarget != selectedPiece)
			{
				//Insert at new position and delete old one
				piece->second.get()->MoveTo({ selectedTarget.x, selectedTarget.y });
				brd.whitePieces.insert_or_assign({ selectedTarget.x, selectedTarget.y }, std::move(brd.whitePieces.find({ selectedPiece.x,selectedPiece.y })->second));
				brd.whitePieces.erase({ selectedPiece.x,selectedPiece.y });
				
				//Check if we're moving our king, if so then update the king's position
				kingInstance = dynamic_cast<King*>(brd.whitePieces.find({ selectedTarget.x, selectedTarget.y })->second.get());
				if (kingInstance != nullptr)
				{
					brd.UpdateWhiteKingLoc({ selectedTarget.x,selectedTarget.y });
					kingInstance = nullptr;
				}

				//Check for taking pieces
				if (brd.blackPieces.count({ selectedTarget.x, selectedTarget.y }) > 0)
				{
					brd.blackPieces.erase({ selectedTarget.x,selectedTarget.y });
				}
						
				//end of turn cleanup
				pieceSelected = false;
				playerTurn = false;
			}					
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
	for (const auto& m : brd.blackPieceTargets)
	if (m == brd.GetWhiteKingLoc())
	{
		checked = true;
		return;
	}
	checked = false;
}
