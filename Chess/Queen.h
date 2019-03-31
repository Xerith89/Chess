#pragma once
#include "Piece.h"

class Queen : public Piece {
public:
	Queen(int x, int y, const std::string spritename, const Board& brd);
	std::vector<std::pair<Coords, Coords>> GetMoves(const Map* mypieces, const Map* opponentpieces, std::set<Coords>& myTargetList, const Coords& enemyKingPos, std::set<Coords>& EnemyTargetList)override;
	std::vector<Coords> GetCheckedMoves(const Map* mypieces, const Map* opponentpieces)override;
private:
};