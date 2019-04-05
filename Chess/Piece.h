#pragma once
#include "Coords.h"
#include "Graphics.h"
#include <vector>
#include <map>
#include <set>
#include <assert.h>
#include <algorithm>

class Board;
class Piece {
protected:
	Board& brd;
	Coords coords;
	Sprite pieceSprite;
	Coords maxCoord = { 7,7 };
	Coords minCoord = { 0,0 };
	Coords startCoords;
	std::vector<std::pair<Coords, Coords>>  moves;
	using Map = std::map<std::pair<int,int>, std::shared_ptr<Piece>>;
	bool whitePiece;
	Coords opponentKingPos;
	Coords myKingPos;
	Map* myPieces;
	Map* opponentPieces;
	std::set<Coords> myTargetList;
	std::set<Coords> opponentTargetList;
	Piece(Coords coords, const std::string spritename, Board& brd, bool whitePiece);
public:
	virtual std::vector<std::pair<Coords, Coords>> GetMoves() = 0;
	virtual void GetTargets(Map* oppoPieces) = 0;
	Coords GetCoords()const;
	Sprite& GetSprite();
	void MoveBy(Coords delta);
	void MoveTo(Coords new_coords);
};