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

	if (wnd.inpt.LeftMsePressed())
	{
		if (!pieceSelected)
		{
			selectedPiece = brd.TranslateCoords(wnd.inpt.GetMseX(), wnd.inpt.GetMseY());
			if (brd.whitePieces.count({ selectedPiece.x,selectedPiece.y }) > 0)
			{
				auto piece = brd.whitePieces.find({ selectedPiece.x,selectedPiece.y });
				pieceSelected = true;
				piece->second->SetSelected(true);
				piece->second->GetMoves(&brd.whitePieces, &brd.blackPieces);
				selectedMoves = piece->second->MoveList();
			}
		}
		else
		{
			//Need to add a check for pieces of the same colour occupying a position in the possible moves list
			//Maybe also colour red underneath if there is an opposing piece at the position
			selectedTarget = brd.TranslateCoords(wnd.inpt.GetMseX(), wnd.inpt.GetMseY());
			if (brd.whitePieces.count({ selectedPiece.x,selectedPiece.y }) > 0)
			{
				auto piece = brd.whitePieces.find({ selectedPiece.x,selectedPiece.y });

				auto i = (std::find(selectedMoves.begin(), selectedMoves.end(), selectedTarget));
				if (i != selectedMoves.end())
				{
					piece->second.get()->MoveTo({ selectedTarget.x, selectedTarget.y });
					brd.whitePieces.insert_or_assign({ selectedTarget.x, selectedTarget.y }, std::move(brd.whitePieces.find({ selectedPiece.x,selectedPiece.y })->second));
					brd.whitePieces.erase({ selectedPiece.x,selectedPiece.y });
					pieceSelected = false;
					selectedPiece.x = 0;
					selectedPiece.y = 0;
				}
			}
		}
	}

	if (wnd.inpt.RightMsePressed())
	{
		if (brd.whitePieces.count({ selectedPiece.x,selectedPiece.y }) > 0)
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
			auto position = brd.TranslateCoords({ m });

			gfx.DrawSprite(position.first, position.second, target);
		}
	}
}
