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

void Piece::MoveBy(Coords delta)
{
	if (coords.x+delta.x >= MinCoord.x && coords.x+delta.x <= MaxCoord.x 
		&& coords.y+delta.y >= MinCoord.y && coords.y+delta.y <= MaxCoord.y)
	{
		coords.x += delta.x;
		coords.y += delta.y;
	}
	
}

void Piece::MoveTo(Coords new_coords)
{
	if (new_coords.x >= MinCoord.x && new_coords.x <= MaxCoord.x && new_coords.y >= MinCoord.y && new_coords.y <= MaxCoord.y)
	{
		coords = new_coords;
	}
}

