#include "Board.h"

Board::Board(const std::string spritename, int x, int y)
	:
	BoardSprite(spritename),
	x(x),
	y(y),
	cellWidth(BoardSprite.GetWidth() / cellsPerRow),
	cellHeight(BoardSprite.GetHeight() / cellsPerRow)
{
}

void Board::DrawBoard(Graphics& gfx)
{
	gfx.DrawSprite(x, y, BoardSprite);
}

int Board::GetCellWidth()
{
	return cellWidth;
}

int Board::GetCellHeight()
{
	return cellHeight;
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

void Board::UpdateWhiteKingLoc(Coords new_loc)
{
	whiteKingLoc = new_loc;
}

Coords Board::GetWhiteKingLoc() const
{
	return whiteKingLoc;
}

void Board::UpdateBlackKingLoc(Coords new_loc)
{
	blackKingLoc = new_loc;
}

Coords Board::GetBlackKingLoc() const
{
	return blackKingLoc;
}

bool Board::CheckValidMove(const Coords from, const Coords to,const bool whitePiece)
{
	//check what colour the piece we're playing is.
	const Map* opponentPieces = &blackPieces;
	auto* opponentTargets = &blackPieceTargets;
	Map myPieces = whitePieces;
	auto myKing = whiteKingLoc;
	
	if (!whitePiece)
	{
		opponentPieces = &whitePieces;
		opponentTargets = &whitePieceTargets;
		myPieces = blackPieces;
		myKing = blackKingLoc;
	}

	//look up the piece with the from coords
	auto piece = myPieces.find({ from.x,from.y });
	
	if (piece != myPieces.end())
	{
		myPieces.insert_or_assign({ to.x, to.y }, std::move(piece->second));
		myPieces.erase({ from.x,from.y });
		
		opponentTargets->clear();
		for (const auto& p : *opponentPieces)
		{
			p.second->GetTargets(&myPieces);
		}
	}
	
	return opponentTargets->count({ myKing }) == 0;
}

