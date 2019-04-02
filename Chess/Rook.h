#pragma once
#include "Piece.h"

class Rook : public Piece {
public:
	Rook(int x, int y, const std::string spritename, const Board& brd);
	virtual std::vector<std::pair<Coords, Coords>> GetMoves(const Map* mypieces, const Map* opponentpieces, std::set<Coords>& myTargetList, const Coords& enemyKingPos, std::set<Coords>& EnemyTargetList, const Coords & myKingPos)override;
	virtual std::vector<std::pair<Coords, Coords>> GetCheckedMoves(const Map* mypieces, const Map* opponentpieces, std::set<Coords>& myTargetList, const Coords& enemyKingPos, std::set<Coords>& EnemyTargetList, const Coords & myKingPos)override;
private:
};