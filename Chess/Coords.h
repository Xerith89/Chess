#pragma once
//Struct to be used to abstract away the concept on pixels in terms to position and replace them with a grid location on our board of cells
struct Coords
{
	int x;
	int y;
	bool operator==(const Coords& rhs)
	{
		return x == rhs.x && y == rhs.y;
	}
	bool operator!=(const Coords& rhs)
	{
		return !operator==(rhs);
	}
};