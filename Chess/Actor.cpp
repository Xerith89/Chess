#include "Actor.h"

Actor::Actor(Window & wnd, Board & brd)
	:
	wnd(wnd),
	brd(brd),
	target("./Sprites/target.bmp"),
	inCheck("./Sprites/checked.bmp")
{
}


bool Actor::GetCMated() const
{
	return cMated;
}
