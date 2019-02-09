#include "Game.h"

Game::Game(Window & wnd)
	:
	wnd(wnd),
	gfx(wnd.GetHandle()),
	brd("./Sprites/board.bmp",100,25)
{
	brd.Pieces.emplace(std::make_pair(0,0), std::make_unique<Pawn>(0, 0, "./Sprites/pawnW.bmp"));

}

void Game::Update()
{
	
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
