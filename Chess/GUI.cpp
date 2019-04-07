#include "GUI.h"

GUI::GUI()
	:
	playedMovesSprite("./Sprites/playedmoves.bmp"),
	helpPlayerSprite("./Sprites/help.bmp")
{
}

void GUI::DrawGUI(Graphics & gfx) const
{
	gfx.DrawSprite(playedMovesX, playedMovesY, playedMovesSprite);
	gfx.DrawSprite(helpPlayerX,helpPlayerY, helpPlayerSprite);
}

