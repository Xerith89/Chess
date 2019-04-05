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

class Actor {
protected:
	Actor(Window& wnd, Board& brd);
	using Map = std::map<std::pair<int, int>, std::shared_ptr<Piece>>;
	King* kingInstance = nullptr;
	bool checked = false;
	bool cMated = false;
	bool promotion = false;
	Sprite target;
	Sprite inCheck;
	Window& wnd;
	Board& brd;
	std::vector<std::pair<Coords, Coords>> movelist;
	virtual void DoTurn() = 0;
	virtual void DrawPieces(Graphics& gfx)const = 0;
	virtual void DrawChecked(Graphics& gfx)const = 0;
	virtual void DrawPromotion(Graphics& gfx)const = 0;
	virtual void TestForCheck() = 0;
	virtual void TestPawnPromotion() = 0;
public:
	bool GetCMated()const;
};