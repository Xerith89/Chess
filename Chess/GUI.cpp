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

void GUI::DrawMoves()
{
	if (ImGui::Begin("Played Moves"))
	{

	}
	ImGui::End();
}

void GUI::DrawHint()
{

}

void GUI::GetAddress()
{
	if (ImGui::Begin("Enter Server Address"))
	{
		ImGui::InputText("address", buffer, sizeof(buffer));
	}
	ImGui::End();
}

std::string GUI::GetBuffer()
{
	return buffer;
}



