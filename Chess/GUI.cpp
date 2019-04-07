#include "GUI.h"

GUI::GUI()
	:
	playedMovesSprite("./Sprites/playedmoves.bmp"),
	helpPlayerSprite("./Sprites/help.bmp"),
	promotionSprite("./Sprites/promoteW.bmp")
{
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
	gfx.DrawSprite(helpPlayerX,helpPlayerY, helpPlayerSprite);
}

void GUI::DrawPromotion(Graphics & gfx) const
{
	gfx.DrawSprite(promotionX, promotionY, promotionSprite);
}

