#pragma once
#include <algorithm>
#undef min
#undef max
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
	bool InbetweenTwoCoords(const Coords& origin, const Coords& dest, const Coords& intersection)const
	{
		
		//check we're above the min x and y value but below the max x and y - therefore inbetween them
		return intersection.x >= std::min(origin.x,intersection.x) && intersection.x <= std::max(dest.x,origin.x) 
		&& intersection.y >= std::min(origin.y, dest.y) && intersection.y <= std::max(origin.y, dest.y);
	}
};