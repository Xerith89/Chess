#pragma once
#include "Piece.h"

class Rook : public Piece {
public:
	Rook(int x, int y, const std::string spritename, const Board& brd);
	void GetMoves(const Map* mypieces, const Map* opponentpieces, std::vector<Coords>& myTargetList, const Coords& enemyKingPos, std::vector<Coords>& EnemyTargetList)override;
private:
};