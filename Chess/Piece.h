#pragma once
#include "Coords.h"
#include "Graphics.h"
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <assert.h>

class Board;
class Piece {
protected:
	const Board& brd;
	Coords coords;
	Sprite pieceSprite;
	Coords maxCoord = { 7,7 };
	Coords minCoord = { 0,0 };
	Coords startCoords;
	bool selected = false;
	std::vector<std::pair<Coords, Coords>>  moves;
	using Map = std::map<std::pair<int,int>, std::unique_ptr<Piece>>;
public:
	Coords GetCoords()const;
	Piece(Coords coords, const std::string spritename, const Board& brd);
	Sprite& GetSprite();
	void MoveBy(Coords delta);
	void MoveTo(Coords new_coords);
	void SetSelected(bool status);
	bool GetSelected()const;
	virtual void GetMoves(const Map* mypieces, const Map* opponentpieces, std::set<Coords>& myTargetList, const Coords& enemyKingPos, std::set<Coords>& EnemyTargetList) = 0;
	std::vector<std::pair<Coords,Coords>> MoveList()const;
};