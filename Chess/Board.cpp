#include "Board.h"

Board::Board(const std::string spritename)
	:
	BoardSprite(spritename)
{
	
}

void Board::DrawBoard(int x, int y, Graphics& gfx) const
{
	gfx.DrawSprite(x, y, BoardSprite);
}
