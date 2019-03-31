#pragma once
#include "Piece.h"

class Bishop : public Piece {
public:
	Bishop(int x, int y, const std::string spritename, const Board& brd);
	void GetMoves(const Map* mypieces, const Map* opponentpieces, std::set<Coords>& myTargetList, const Coords& enemyKingPos, std::set<Coords>& EnemyTargetList)override;
	std::vector<Coords> GetCheckedMoves(const Map* mypieces, const Map* opponentpieces)override;
private:
};