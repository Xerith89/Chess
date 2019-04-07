#include "MyWindows.h"
#include "Piece.h"

Coords Piece::GetCoords()const
{
	return coords;
}

Piece::Piece(Coords coords, const std::string spritename, Board& brd,bool white)
	:
	coords(coords),
	pieceSprite(spritename),
	brd(brd),
	whitePiece(white)
{
}

Sprite& Piece::GetSprite()
{
	return pieceSprite;
}

void Piece::MoveBy(Coords delta)
{
	if (coords.x+delta.x >= minCoord.x && coords.x+delta.x <= maxCoord.x 
		&& coords.y+delta.y >= minCoord.y && coords.y+delta.y <= maxCoord.y)
	{
		coords.x += delta.x;
		coords.y += delta.y;
	}
	
}

void Piece::MoveTo(Coords new_coords)
{
	if (new_coords.x >= minCoord.x && new_coords.x <= maxCoord.x && new_coords.y >= minCoord.y && new_coords.y <= maxCoord.y)
	{
		coords = new_coords;
	}
}

