#include "GUI.h"

GUI::GUI(Board& brd)
	:
	promotionSprite("./Sprites/promoteW.bmp"),
	blackPromotionSprite("./Sprites/promoteB.bmp"),
	brd(brd)
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

void GUI::DrawGui(bool multiplayer)
{
	if (ImGui::Begin("Played Moves"))
	{
		ImGui::SetWindowPos(ImVec2(550, 20));
		ImGui::SetWindowSize(ImVec2(240, 450));

		for (const auto& m : brd.playedMoves)
		{
			std::stringstream text;
			text << letters.at(m.first.x) << numbers.at(m.first.y) << " to " << letters.at(m.second.x) << numbers.at(m.second.y);
			ImGui::Text(text.str().c_str());
		}
	}
	ImGui::End();


	if (!multiplayer && ImGui::Begin("Hint"))
	{
		ImGui::SetWindowPos(ImVec2(580, 490));
		ImGui::SetWindowSize(ImVec2(150, 85));
		ImGui::Button("Hint", ImVec2(128, 50));
	}
	ImGui::End();
	
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



