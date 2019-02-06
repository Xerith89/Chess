#include "Game.h"

void Game::Render()
{
}

void Game::Update()
{
}

Game::Game(Window & wnd)
	:
	wnd(wnd),
	gfx(wnd.GetHandle())
{
}

void Game::Run()
{
	Update();
	Render();
	gfx.RenderFrame();
}
