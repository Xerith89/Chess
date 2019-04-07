#pragma once
#include "MyWindows.h"
#include <map>
#include <vector>
#include "Piece.h"
#include "Board.h"
#include <random>
#include <assert.h>
#include "King.h"
#include "Pawn.h"
#include "Bishop.h"
#include "Knight.h"
#include "Queen.h"
#include "Rook.h"
#include <algorithm>

class Actor {
protected:
	Actor(Window& wnd, Board& brd);
	using Map = std::map<std::pair<int, int>, std::shared_ptr<Piece>>;
	King* kingInstance = nullptr;
	Pawn* pawnInstance = nullptr;
	bool checked = false;
	bool cMated = false;
	bool promotion = false;
	bool stalemate = false;
	Sprite target;
	Sprite inCheck;
	Window& wnd;
	Board& brd;
	std::vector<std::pair<Coords, Coords>> movelist;
	virtual void DoTurn() = 0;
	virtual void DrawPieces(Graphics& gfx)const = 0;
	virtual void DrawChecked(Graphics& gfx)const = 0;
	virtual void TestForCheck() = 0;
	virtual bool TestForCheckMate() = 0;
	virtual void TestForStaleMate() = 0;
	virtual void Promote(Map* map) = 0;
public:
	bool GetCheckMated()const;
	bool GetStaleMated()const;
	bool GetPromotion()const;
};