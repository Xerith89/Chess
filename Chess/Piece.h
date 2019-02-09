#pragma once
#include "Coords.h"
#include "Graphics.h"

class Piece {
private:
	Coords coords;
	Sprite pieceSprite;
public:
	Coords GetCoords()const;
	Piece(Coords coords, const std::string spritename);
	Sprite& GetSprite();
};