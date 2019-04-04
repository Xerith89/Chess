#pragma once
#include "MyWindows.h"
#include <map>
#include <vector>
#include "Piece.h"
#include "Board.h"
#include <random>
#include <assert.h>
#include "King.h"
#include <algorithm>

class Opponent{
	using Map = std::map<std::pair<int, int>, std::shared_ptr<Piece>>;
public:
	Opponent(Board& brd);
	void DoTurn();
	bool GetCmated()const;
	void DrawPieces(Graphics& gfx)const;
	void DrawChecked(Graphics& gfx)const;
	void TestForCheck();
private:
	Sprite inCheck;
	std::vector<std::pair<Coords, Coords>> movelist;
	bool checked = false;
	bool cmated = false;
	void GenerationZero();
	bool humanOpponent;
	Board& brd;
	std::random_device rd;
	std::mt19937 rng;
	King* kingInstance = nullptr;
};