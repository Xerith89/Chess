#include "Piece.h"

bool Piece::InbetweenCoords(const Coords & origin, const Coords & dest,const Coords& intersecting) const
{
		//check we're above the min x and y value but below the max x and y - therefore inbetween them
		return intersecting.x >= std::min(origin.x, coords.x) && intersecting.x <= std::max(dest.x, origin.x)
			&& intersecting.y >= std::min(origin.y, dest.y) && intersecting.y <= std::max(origin.y, dest.y);
	
}

Coords Piece::GetCoords()const
{
	return coords;
}

Piece::Piece(Coords coords, const std::string spritename, Board& brd,bool white)
	:
	coords(coords),
	startCoords(coords),
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

