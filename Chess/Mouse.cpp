#include "Mouse.h"

std::pair<int, int> Mouse::GetPos() const
{
	return { x, y };
}

int Mouse::GetX() const
{
	return x;
}

int Mouse::GetY() const
{
	return y;
}

bool Mouse::LeftPressed() const
{
	return leftPressed;
}

bool Mouse::RightPressed() const
{
	return rightPressed;
}

void Mouse::UpdatePos(int new_x, int new_y)
{
	x = new_x;
	y = new_y;
}


