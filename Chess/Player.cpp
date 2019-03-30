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
		if (!pieceSelected || selectedMoves.size() == 0)
		{
			//Translate the mouse position to board coords
			selectedPiece = brd.TranslateCoords(wnd.inpt.GetMseX(), wnd.inpt.GetMseY());

			if (brd.whitePieces.find({ selectedPiece.x,selectedPiece.y }) != brd.whitePieces.end())
			{
				//If the piece exists then  get the moves for it
				pieceSelected = true;
				brd.whitePieces.find({ selectedPiece.x,selectedPiece.y })->second->SetSelected(true);
				brd.whitePieces.find({ selectedPiece.x,selectedPiece.y })->second->GetMoves(&brd.whitePieces, &brd.blackPieces);
				for (const auto& p : brd.whitePieces.find({ selectedPiece.x,selectedPiece.y })->second->MoveList())
				{
					selectedMoves.push_back(p.second);
				}
			}
		}
		else
		{
			//We already have a target so we're clicking on a new position - do the usual translate
			selectedTarget = brd.TranslateCoords(wnd.inpt.GetMseX(), wnd.inpt.GetMseY());

			if (selectedTarget != selectedPiece && brd.whitePieces.find({ selectedPiece.x,selectedPiece.y }) != brd.whitePieces.end())
			{
				//Insert at new position and delete old one
				brd.whitePieces.find({ selectedPiece.x,selectedPiece.y })->second.get()->MoveTo({ selectedTarget.x, selectedTarget.y });
				brd.whitePieces.insert_or_assign({ selectedTarget.x, selectedTarget.y }, std::move(brd.whitePieces.find({ selectedPiece.x,selectedPiece.y })->second));
				brd.whitePieces.erase({ selectedPiece.x,selectedPiece.y });					
				pieceSelected = false;
				selectedPiece.x = 0;
				selectedPiece.y = 0;
				playerTurn = false;

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
		if (brd.whitePieces.find({ selectedPiece.x,selectedPiece.y })!= brd.whitePieces.end())
		{
			brd.whitePieces.find({ selectedPiece.x,selectedPiece.y })->second->SetSelected(false);
			pieceSelected = false;
			selectedPiece.x = 0;
			selectedPiece.y = 0;
		}
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


