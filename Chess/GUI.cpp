#include "GUI.h"

GUI::GUI()
	:
	promotionSprite("./Sprites/promoteW.bmp"),
	blackPromotionSprite("./Sprites/promoteB.bmp")
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

void GUI::DrawPromotionBlack(Graphics& gfx) const
{
	gfx.DrawSprite(promotionX, promotionY, blackPromotionSprite);
}

void GUI::DrawPromotion(Graphics & gfx) const
{
	gfx.DrawSprite(promotionX, promotionY, promotionSprite);
}



