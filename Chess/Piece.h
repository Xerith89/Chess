#pragma once
#include "Coords.h"
#include "Graphics.h"
#include <vector>
#include <map>
#include <set>
#include <assert.h>
#include <algorithm>
#undef min
#undef max

class Board;
class Piece {
protected:
	Board& brd;
	Coords coords;
	Sprite pieceSprite;
	Coords maxCoord = { 7,7 };
	Coords minCoord = { 0,0 };
	Coords startCoords;
	bool selected = false;
	std::vector<std::pair<Coords, Coords>>  moves;
	using Map = std::map<std::pair<int,int>, std::unique_ptr<Piece>>;
	bool InbetweenCoords(const Coords& origin, const Coords& dest, const Coords& intersecting)const;
	bool whitePiece;
	Coords opponentKingPos;
	Coords myKingPos;
	Map* myPieces;
	Map* opponentPieces;
	std::set<Coords> myTargetList;
	std::set<Coords> opponentTargetList;
public:
	Coords GetCoords()const;
	Piece(Coords coords, const std::string spritename, Board& brd, bool whitePiece);
	Sprite& GetSprite();
	void MoveBy(Coords delta);
	void MoveTo(Coords new_coords);
	void SetSelected(bool status);
	bool GetSelected()const;
	virtual std::vector<std::pair<Coords, Coords>> GetMoves() = 0;
	virtual std::vector<std::pair<Coords, Coords>> GetCheckedMoves() = 0;
};