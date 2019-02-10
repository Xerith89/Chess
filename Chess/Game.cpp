#include "Game.h"

Game::Game(Window & wnd)
	:
	wnd(wnd),
	gfx(wnd.GetHandle()),
	brd("./Sprites/board.bmp",100,25)
{
	for (int i = 0; i < 8; i++)
	{
		std::unique_ptr<Piece> pawn;
		brd.whitePieces.emplace(std::make_pair(i,6), std::make_unique<Pawn>(i, 6, "./Sprites/pawnW.bmp"));
		brd.blackPieces.emplace(std::make_pair(i,1), std::make_unique<Pawn>(i, 1, "./Sprites/pawnB.bmp"));
	}

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
