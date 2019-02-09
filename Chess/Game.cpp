#include "Game.h"

Game::Game(Window & wnd)
	:
	wnd(wnd),
	gfx(wnd.GetHandle()),
	brd("./Sprites/board.bmp",100,25)
{
	
}

void Game::Update()
{
	brd.UpdateBoard(wnd);
}

void Game::Render()
{
	brd.DrawBoard(gfx);
}

void Game::Run()
{
	gfx.PrepareFrame();
	Update();
	Render();
	gfx.RenderFrame();
}
