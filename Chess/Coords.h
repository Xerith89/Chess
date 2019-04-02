#pragma once

//Struct to be used to abstract away the concept on pixels in terms to position and replace them with a grid location on our board of cells
struct Coords
{
	int x;
	int y;
	bool operator==(const Coords& rhs)const
	{
		return x == rhs.x && y == rhs.y;
	}
	bool operator!=(const Coords& rhs)const
	{
		return !operator==(rhs);
	}
	bool operator<(const Coords& rhs)const
	{
		return (x < rhs.x) || (x == rhs.x) && (y < rhs.y);
	}
	
};