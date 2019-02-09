#include "Game.h"

Game::Game(Window & wnd)
	:
	wnd(wnd),
	gfx(wnd.GetHandle()),
	brd("./Sprites/board.bmp")
{
	
}

void Game::Update()
{
}

void Game::Render()
{
	brd.DrawBoard(100, 25, gfx);
}

void Game::Run()
{
	gfx.PrepareFrame();
	Update();
	Render();
	gfx.RenderFrame();
}
