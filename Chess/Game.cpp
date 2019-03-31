#include "Game.h"


/*
BUG LIST
.You can take Kings
.You can move into check positions
.If you click a piece with no moves available, select a pawn then deselect it - you can't get the moves back for the pawn
.Check doesn't acknowledge pawn take semantics
*/

Game::Game(Window & wnd)
	:
	wnd(wnd),
	gfx(wnd.GetHandle()),
	brd("./Sprites/board.bmp",100,25),
	player(wnd,brd),
	opponent(brd)
{
	//Kings
	brd.whitePieces.emplace(std::make_pair(4, 7), std::make_unique<King>(4, 7, "./Sprites/kingW.bmp"));
	brd.blackPieces.emplace(std::make_pair(4, 0), std::make_unique<King>(4, 0, "./Sprites/kingB.bmp"));
	//Queens
	brd.whitePieces.emplace(std::make_pair(3,7), std::make_unique<Queen>(3, 7, "./Sprites/queenW.bmp"));
	brd.blackPieces.emplace(std::make_pair(3,0), std::make_unique<Queen>(3, 0, "./Sprites/queenB.bmp"));
	//Bishops
	brd.whitePieces.emplace(std::make_pair(2, 7), std::make_unique<Bishop>(2, 7, "./Sprites/bishopW.bmp"));
	brd.whitePieces.emplace(std::make_pair(5, 7), std::make_unique<Bishop>(5, 7, "./Sprites/bishopW.bmp"));
	
	brd.blackPieces.emplace(std::make_pair(2, 0), std::make_unique<Bishop>(2, 0, "./Sprites/bishopB.bmp"));
	brd.blackPieces.emplace(std::make_pair(5, 0), std::make_unique<Bishop>(5, 0, "./Sprites/bishopb.bmp"));
	//Knights
	brd.whitePieces.emplace(std::make_pair(1, 7), std::make_unique<Knight>(1, 7, "./Sprites/knightW.bmp"));
	brd.whitePieces.emplace(std::make_pair(6, 7), std::make_unique<Knight>(6, 7, "./Sprites/knightW.bmp"));

	brd.blackPieces.emplace(std::make_pair(1, 0), std::make_unique<Knight>(1, 0, "./Sprites/knightB.bmp"));
	brd.blackPieces.emplace(std::make_pair(6, 0), std::make_unique<Knight>(6, 0, "./Sprites/knightB.bmp"));
	//Rooks
	brd.whitePieces.emplace(std::make_pair(0, 7), std::make_unique<Rook>(0, 7, "./Sprites/rookW.bmp"));
	brd.whitePieces.emplace(std::make_pair(7, 7), std::make_unique<Rook>(7, 7, "./Sprites/rookW.bmp"));

	brd.blackPieces.emplace(std::make_pair(0, 0), std::make_unique<Rook>(0, 0, "./Sprites/rookB.bmp"));
	brd.blackPieces.emplace(std::make_pair(7, 0), std::make_unique<Rook>(7, 0, "./Sprites/rookB.bmp"));
	//Pawns
	for (int i = 0; i < 8; i++)
	{
		brd.whitePieces.emplace(std::make_pair(i,6), std::make_unique<Pawn>(i, 6, "./Sprites/pawnW.bmp",true));
		brd.blackPieces.emplace(std::make_pair(i,1), std::make_unique<Pawn>(i, 1, "./Sprites/pawnB.bmp",false));
	}

}

void Game::Update()
{
	if (player.PlayerTurn())
	{
		player.DoTurn();
	}
	if (!player.PlayerTurn())
	{
		opponent.DoTurn();
		player.SetPlayerTurn();
	}
}

void Game::Render()
{
	brd.DrawBoard(gfx);
	player.DrawPossibleMoves(gfx);
}

void Game::Run()
{
	gfx.PrepareFrame();
	Update();
	Render();
	gfx.RenderFrame();
}

