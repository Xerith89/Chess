#include "Board.h"

Board::Board(const std::string spritename, int x, int y)
	:
	BoardSprite(spritename),
	x(x),
	y(y),
	cellWidth(BoardSprite.GetWidth() / cellsPerRow),
	cellHeight(BoardSprite.GetHeight() / cellsPerRow),
	target("./Sprites/target.bmp")
{
}

void Board::DrawBoard(Graphics& gfx)
{
	gfx.DrawSprite(x, y, BoardSprite);

	for (const auto& x : whitePieces)
	{
		auto position = TranslateCoords(x.second.get());
		gfx.DrawSprite(position.first, position.second, x.second->GetSprite());
	}

	if (whitePieces.count({ selectedPiece.x, selectedPiece.y }) > 0)
	{
		const auto moves = whitePieces.find({ selectedPiece.x, selectedPiece.y })->second.get()->MoveList();

		for (const auto& m : moves)
		{
			auto position = TranslateCoords({ m });

			gfx.DrawSprite(position.first, position.second, target);
		}
	}

	for (const auto& x : blackPieces)
	{
		auto position = TranslateCoords(x.second.get());
		gfx.DrawSprite(position.first, position.second, x.second->GetSprite());
	}
}

int Board::GetCellWidth()
{
	return cellWidth;
}

int Board::GetCellHeight()
{
	return cellHeight;
}

void Board::UpdateBoard(Window & wnd)
{

	if (wnd.inpt.LeftMsePressed())
	{
		if (!pieceSelected)
		{
			selectedPiece = TranslateCoords(wnd.inpt.GetMseX(), wnd.inpt.GetMseY());
			if (whitePieces.count({ selectedPiece.x,selectedPiece.y }) > 0)
			{
				auto piece = whitePieces.find({ selectedPiece.x,selectedPiece.y });
				pieceSelected = true;
				piece->second->SetSelected(true);
				piece->second->GetMoves();
				selectedMoves = piece->second->MoveList();
			}
		}
		else
		{
			//Need to add a check for pieces of the same colour occupying a position in the possible moves list
			//Maybe also colour red underneath if there is an opposing piece at the position
			selectedTarget = TranslateCoords(wnd.inpt.GetMseX(), wnd.inpt.GetMseY());
			if (whitePieces.count({ selectedPiece.x,selectedPiece.y }) > 0)
			{
				auto piece = whitePieces.find({ selectedPiece.x,selectedPiece.y });
				
				auto i = (std::find(selectedMoves.begin(), selectedMoves.end(), selectedTarget));
				if (i != selectedMoves.end())
				{
					piece->second.get()->MoveTo({ selectedTarget.x, selectedTarget.y });
					whitePieces.insert_or_assign({ selectedTarget.x, selectedTarget.y }, std::move(whitePieces.find({ selectedPiece.x,selectedPiece.y })->second));
					whitePieces.erase({ selectedPiece.x,selectedPiece.y });
					pieceSelected = false;
					selectedPiece.x = 0;
					selectedPiece.y = 0;
				}
			}
		}
	}

	if (wnd.inpt.RightMsePressed())
	{
		if (whitePieces.count({ selectedPiece.x,selectedPiece.y }) > 0)
		{
			whitePieces.find({ selectedPiece.x,selectedPiece.y })->second->SetSelected(false);
			pieceSelected = false;
			selectedPiece.x = 0;
			selectedPiece.y = 0;
		}
	}
}

std::pair<int, int> Board::TranslateCoords(Piece* piece)
{
	int x_in = piece->GetCoords().x;
	int y_in = piece->GetCoords().y;
	
	//Check we are in the board boundaries - if we aren't, something went wrong and we just return out current position
	if (x_in < 0 || x_in > 7 || y_in < 0 || y_in > 7)
	{
		return std::make_pair(x_in*cellWidth, y_in*cellHeight);
	}

	int sprite_width = piece->GetSprite().GetWidth();
	int sprite_height = piece->GetSprite().GetHeight();
	//Center the sprite in the middle of the cell
	int x_out = x + (x_in*cellWidth) + ((cellWidth-sprite_width)/2);
	int y_out = y + (y_in*cellHeight) + ((cellHeight-sprite_height)/2);
	
	return std::make_pair(x_out,y_out);
}

Coords Board::TranslateCoords(int x_in, int y_in)
{//Check we're actually clicking inside the board
	if (x_in >= x && x_in <= x+BoardSprite.GetWidth() && y_in >= y && y_in <= y+BoardSprite.GetHeight())
	{
		//Convert from window space to board space
		int x_coord = (x_in-x) / cellWidth;
		int y_coord = (y_in-y) / cellHeight;
		
		return { x_coord,y_coord };
	}
	//If we get here then we clicked outside of the board so we will discard
	return { -1,-1 };
}

std::pair<int, int> Board::TranslateCoords(Coords coords_in)
{
	int x_out = x+coords_in.x*cellWidth;
	int y_out =y+coords_in.y*cellHeight;
	return std::make_pair(x_out, y_out);
}

