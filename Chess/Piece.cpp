#include "Piece.h"

Coords Piece::GetCoords()const
{
	return coords;
}

Piece::Piece(Coords coords, const std::string spritename)
	:
	coords(coords),
	pieceSprite(spritename)
{
}

Sprite& Piece::GetSprite()
{
	return pieceSprite;
}

