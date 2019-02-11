#pragma once
#include "Coords.h"
#include "Graphics.h"
#include <vector>
#include <map>
#include <algorithm>

class Piece {
protected:
	Coords coords;
	Sprite pieceSprite;
	Coords maxCoord = { 7,7 };
	Coords minCoord = { 0,0 };
	Coords startCoords;
	bool selected = false;
	std::vector<Coords> movesTemplate;
	std::vector<Coords> moves;
	using Map = std::map<std::pair<int,int>, std::unique_ptr<Piece>>;
public:
	Coords GetCoords()const;
	Piece(Coords coords, const std::string spritename);
	Sprite& GetSprite();
	void MoveBy(Coords delta);
	void MoveTo(Coords new_coords);
	void SetSelected(bool status);
	bool GetSelected()const;
	virtual void GetMoves(Map* white, Map* black) = 0;
	std::vector<Coords> MoveList()const;
};