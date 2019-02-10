#include "King.h"

King::King(int x, int y, const std::string spritename)
	:
	Piece({ x,y }, spritename)
{
	//right
	movesTemplate.push_back({ 1,0 });
	//down
	movesTemplate.push_back({ 0,1 });
	//up
	movesTemplate.push_back({ 0,-1 });
	//left
	movesTemplate.push_back({ -1,0 });
	//diagonal downright
	movesTemplate.push_back({ 1,1 });
	//diagonal upright
	movesTemplate.push_back({ 1,-1});
	//diagonal downleft
	movesTemplate.push_back({ -1,1 });
	//diagonal upleft
	movesTemplate.push_back({ -1,-1 });	
}

void King::GetMoves()
{
}
