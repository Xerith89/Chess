#include "Game.h"

Game::Game(Window & wnd)
	:
	wnd(wnd),
	gfx(wnd.GetHandle()),
{
	
}

void Game::Update()
{
}

void Game::Render()
{
}

void Game::Run()
{
	gfx.PrepareFrame();
	Update();
	Render();
	gfx.RenderFrame();
}
