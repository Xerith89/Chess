#include "Actor.h"

Actor::Actor(Window & wnd, Board & brd)
	:
	wnd(wnd),
	brd(brd),
	target("./Sprites/target.bmp"),
	inCheck("./Sprites/checked.bmp")
{
}

bool Actor::GetCheckMated() const
{
	return cMated;
}

bool Actor::GetStaleMated() const
{
	return stalemate;
}

bool Actor::GetPromotion() const
{
	return promotion;
}

bool Actor::GetChecked() const
{
	return checked;
}
