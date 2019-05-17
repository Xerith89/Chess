#include "GUI.h"

void GUI::TranslateCordToSprite(Coords in)
{
}

GUI::GUI(Board& brd)
	:
	playedMovesSprite("./Sprites/playedmoves.bmp"),
	helpPlayerSprite("./Sprites/help.bmp"),
	promotionSprite("./Sprites/promoteW.bmp"),
	blackPromotionSprite("./Sprites/promoteB.bmp"),
	to("./Sprites/Characters/to.bmp"),
	brd(brd)
{
	
	letters.emplace_back("./Sprites/Characters/a.bmp"),
	letters.emplace_back("./Sprites/Characters/b.bmp"),
	letters.emplace_back("./Sprites/Characters/c.bmp"),
	letters.emplace_back("./Sprites/Characters/d.bmp"),
	letters.emplace_back("./Sprites/Characters/e.bmp"),
	letters.emplace_back("./Sprites/Characters/f.bmp"),
	letters.emplace_back("./Sprites/Characters/g.bmp"),
	letters.emplace_back("./Sprites/Characters/h.bmp");

	numbers.emplace_back("./Sprites/Characters/8.bmp"),
	numbers.emplace_back("./Sprites/Characters/7.bmp"),
	numbers.emplace_back("./Sprites/Characters/6.bmp"),
	numbers.emplace_back("./Sprites/Characters/5.bmp"),
	numbers.emplace_back("./Sprites/Characters/4.bmp"),
	numbers.emplace_back("./Sprites/Characters/3.bmp"),
	numbers.emplace_back("./Sprites/Characters/2.bmp"),
	numbers.emplace_back("./Sprites/Characters/1.bmp");
}

int GUI::GetPromoteGraphicX() const
{
	return promotionX;
}

int GUI::GetPromoteGraphicY() const
{
	return promotionY;
}

void GUI::DrawGUI(Graphics & gfx) const
{
	gfx.DrawSprite(playedMovesX, playedMovesY, playedMovesSprite);
	size_t i = 0;
	size_t yPos = 0;
	if (brd.playedMoves.size() > 12)
	{
		i += (brd.playedMoves.size() % 12);
	}
	for (; i < brd.playedMoves.size(); i++,yPos++)
	{
		if (yPos >= 12)
		{
			yPos = 0;
		}
		gfx.DrawSprite(playedMovesX + xOffset, yStart + yPos * yOffset, letters.at(brd.playedMoves.at(i).first.x));
		gfx.DrawSprite(playedMovesX + (xOffset * 2), yStart + yPos * yOffset, numbers.at(brd.playedMoves.at(i).first.y));
		gfx.DrawSprite(playedMovesX + (xOffset * 3), yStart + yPos * yOffset, to);
		gfx.DrawSprite(playedMovesX + (xOffset * 5), yStart + yPos * yOffset, letters.at(brd.playedMoves.at(i).second.x));
		gfx.DrawSprite(playedMovesX + (xOffset * 6), yStart + yPos * yOffset, numbers.at(brd.playedMoves.at(i).second.y));
	}
	gfx.DrawSprite(helpPlayerX,helpPlayerY, helpPlayerSprite);
}

void GUI::DrawPromotionBlack(Graphics& gfx) const
{
	gfx.DrawSprite(promotionX, promotionY, blackPromotionSprite);
}

void GUI::DrawPromotion(Graphics & gfx) const
{
	gfx.DrawSprite(promotionX, promotionY, promotionSprite);
}

