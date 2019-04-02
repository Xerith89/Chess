#pragma once
#include "Piece.h"

class Pawn : public Piece {
public:
	Pawn(int x, int y, const std::string spritename, bool white, const Board& brd);
	virtual std::vector<std::pair<Coords, Coords>> GetMoves(const Map* mypieces, const Map* opponentpieces, std::set<Coords>& myTargetList, const Coords& enemyKingPos, std::set<Coords>& EnemyTargetList, const Coords & myKingPos)override;
	virtual std::vector<std::pair<Coords, Coords>> GetCheckedMoves(const Map* mypieces, const Map* opponentpieces, std::set<Coords>& myTargetList, const Coords& enemyKingPos, std::set<Coords>& EnemyTargetList, const Coords & myKingPos)override;
private:
	//Pawns can go two spaces in their first move so this will be used to populate move list each selection
	bool firstMove = true;
	bool whitePiece;
	int attackOffset = 1;
	int y_offset;
};