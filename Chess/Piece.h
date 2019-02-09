#pragma once
#include "Coords.h"
#include "Graphics.h"

class Piece {
private:
	Coords coords;
	Sprite pieceSprite;
	Coords MaxCoord = { 7,7 };
	Coords MinCoord = { 0,0 };
public:
	Coords GetCoords()const;
	Piece(Coords coords, const std::string spritename);
	Sprite& GetSprite();
	void MoveBy(Coords delta);
	void MoveTo(Coords new_coords);
};