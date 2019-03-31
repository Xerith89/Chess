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
			selectedMoves.clear();
			//Translate the mouse position to board coords
			selectedPiece = brd.TranslateCoords(wnd.inpt.GetMseX(), wnd.inpt.GetMseY());
			auto piece = brd.whitePieces.find({ selectedPiece.x,selectedPiece.y });
			if (piece != brd.whitePieces.end())
			{
				TestForCheck();
				//If the piece exists then store it and get the moves for it
				pieceSelected = true;
				piece->second->GetMoves(&brd.whitePieces, &brd.blackPieces);
				for (const auto& p : piece->second->MoveList())
				{
					selectedMoves.push_back(p.second);
				}
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
			if (piece != brd.whitePieces.end())
			{
				auto i = (std::find(selectedMoves.begin(), selectedMoves.end(), selectedTarget));
				if (i != selectedMoves.end() && selectedTarget != selectedPiece)
				{
					//Insert at new position and delete old one
					piece->second.get()->MoveTo({ selectedTarget.x, selectedTarget.y });
					brd.whitePieces.insert_or_assign({ selectedTarget.x, selectedTarget.y }, std::move(brd.whitePieces.find({ selectedPiece.x,selectedPiece.y })->second));
					brd.whitePieces.erase({ selectedPiece.x,selectedPiece.y });
					
					//Check if we're moving our king, if so then update the king's position
					kingInstance = dynamic_cast<King*>(brd.whitePieces.find({ selectedTarget.x, selectedTarget.y })->second.get());
					if (kingInstance != nullptr)
					{
						kingLoc = { selectedTarget.x,selectedTarget.y };
						kingInstance = nullptr;
					}
					
					//end of turn cleanup
					pieceSelected = false;
					playerTurn = false;					
				}
				//Check for taking pieces
				if (brd.blackPieces.count({ selectedTarget.x, selectedTarget.y }) > 0)
				{
					brd.blackPieces.erase({ selectedTarget.x,selectedTarget.y });
				}
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
	if (brd.whitePieces.count({ selectedPiece.x, selectedPiece.y }) > 0)
	{
		const auto moves = brd.whitePieces.find({ selectedPiece.x, selectedPiece.y })->second.get()->MoveList();

		for (const auto& m : moves)
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

Coords Player::GetKingPosition() const
{
	return kingLoc;
}

void Player::TestForCheck()
{
	//Go through each piece and check if its target is our king,
	//if any target equals our king location then we're in check
	for (Map::iterator it = brd.blackPieces.begin(); it != brd.blackPieces.end(); it++)
	{
		it->second->GetMoves(&brd.blackPieces,&brd.whitePieces);
		for (const auto& m : it->second->MoveList())
			if (m.second == kingLoc)
			{
				checked = true;
				return;
			}
	}
	checked = false;
}
