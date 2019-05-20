#pragma once
#include "Coords.h"
#include "Graphics.h"
#include <vector>
#include <map>
#include <set>
#include <assert.h>
#include <algorithm>
#include <array>

class Board;
class Piece {
protected:
	Piece(Coords coords, const std::string spritename, Board& brd, bool whitePiece);
	Board& brd;
	Coords coords;
	Sprite pieceSprite;
	Coords maxCoord = { 7,7 };
	Coords minCoord = { 0,0 };
	using Map = std::map<std::pair<int,int>, std::shared_ptr<Piece>>;
	bool whitePiece;
	Coords opponentKingPos;
	Coords myKingPos;
	//References to maps containing colour's pieces
	Map* myPieces;
	Map* opponentPieces;
	//Local version of the target list for each piece
	std::set<Coords> myTargetList;
	std::set<Coords> opponentTargetList;
	std::vector<std::pair<Coords, Coords>>  moves;
public:
	virtual std::vector<std::pair<Coords, Coords>> GetMoves() = 0;
	virtual void GetTargets(Map* oppoPieces) = 0;
	Coords GetCoords()const;
	Sprite& GetSprite();
	void MoveTo(Coords new_coords);
	virtual int GetScore() = 0;
	virtual int GetBetterScore() = 0;
};