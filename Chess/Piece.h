#pragma once
#include "Coords.h"
#include "Graphics.h"

class Piece {
protected:
	Coords coords;
	Sprite pieceSprite;
	Coords maxCoord = { 7,7 };
	Coords minCoord = { 0,0 };
	bool selected = false;
public:
	Coords GetCoords()const;
	Piece(Coords coords, const std::string spritename);
	Sprite& GetSprite();
	void MoveBy(Coords delta);
	void MoveTo(Coords new_coords);
	void SetSelected(bool status);
	bool GetSelected()const;
	//virtual void GetMoves() = 0;
};