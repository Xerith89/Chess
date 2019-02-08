#include "Game.h"

Game::Game(Window & wnd)
	:
	wnd(wnd),
	gfx(wnd.GetHandle())
{
}

void Game::Update()
{
}

void Game::Render()
{
	gfx.SetPixel(200, 200, Color(255, 255, 255, 255));
}

void Game::Run()
{
	gfx.PrepareFrame();
	Update();
	Render();
	gfx.RenderFrame();
}
