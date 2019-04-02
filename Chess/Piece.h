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
	const Board& brd;
	Coords coords;
	Sprite pieceSprite;
	Coords maxCoord = { 7,7 };
	Coords minCoord = { 0,0 };
	Coords startCoords;
	bool selected = false;
	std::vector<std::pair<Coords, Coords>>  moves;
	using Map = std::map<std::pair<int,int>, std::unique_ptr<Piece>>;
	bool InbetweenCoords(const Coords& origin, const Coords& dest, const Coords& intersecting)const;
public:
	Coords GetCoords()const;
	Piece(Coords coords, const std::string spritename, const Board& brd);
	Sprite& GetSprite();
	void MoveBy(Coords delta);
	void MoveTo(Coords new_coords);
	void SetSelected(bool status);
	bool GetSelected()const;
	virtual std::vector<std::pair<Coords, Coords>> GetMoves(const Map* mypieces, const Map* opponentpieces, std::set<Coords>& myTargetList, const Coords& enemyKingPos, std::set<Coords>& EnemyTargetList, const Coords & myKingPos) = 0;
	virtual std::vector<std::pair<Coords, Coords>> GetCheckedMoves(const Map* mypieces, const Map* opponentpieces, std::set<Coords>& myTargetList, const Coords& enemyKingPos, std::set<Coords>& EnemyTargetList, const Coords & myKingPos) = 0;
};