#include "Game.h"


/*
BUG LIST
.Padding issue for bitmap loading causing graphical glitch
TODO LIST
.Enpassant
.Castling
.Drawn games
.Generational Minimax AI
.Player best move
.Played moves written to screen
.Menu Screens
.Sounds
.Multiplayer
*/

Game::Game(Window & wnd)
	:
	wnd(wnd),
	gfx(wnd.GetHandle()),
	brd("./Sprites/board.bmp",30,25),
	player(wnd,brd),
	opponent(wnd,brd),
	gui()
{
	//Kings
	brd.whitePieces.emplace(std::make_pair(4, 7), std::make_shared<King>(4, 7, "./Sprites/kingW.bmp",true,brd));
	brd.blackPieces.emplace(std::make_pair(4, 0), std::make_shared<King>(4, 0, "./Sprites/kingB.bmp",false,brd));
	//Queens
	brd.whitePieces.emplace(std::make_pair(3,7), std::make_shared<Queen>(3, 7, "./Sprites/queenW.bmp",true,brd));
	brd.blackPieces.emplace(std::make_pair(3,0), std::make_shared<Queen>(3, 0, "./Sprites/queenB.bmp",false,brd));
	//Bishops
	brd.whitePieces.emplace(std::make_pair(2, 7), std::make_shared<Bishop>(2, 7, "./Sprites/bishopW.bmp",true,brd));
	brd.whitePieces.emplace(std::make_pair(5, 7), std::make_shared<Bishop>(5, 7, "./Sprites/bishopW.bmp",true,brd));
	
	brd.blackPieces.emplace(std::make_pair(2, 0), std::make_shared<Bishop>(2, 0, "./Sprites/bishopB.bmp",false,brd));
	brd.blackPieces.emplace(std::make_pair(5, 0), std::make_shared<Bishop>(5, 0, "./Sprites/bishopb.bmp",false,brd));
	//Knights
	brd.whitePieces.emplace(std::make_pair(1, 7), std::make_shared<Knight>(1, 7, "./Sprites/knightW.bmp",true,brd));
	brd.whitePieces.emplace(std::make_pair(6, 7), std::make_shared<Knight>(6, 7, "./Sprites/knightW.bmp",true,brd));

	brd.blackPieces.emplace(std::make_pair(1, 0), std::make_shared<Knight>(1, 0, "./Sprites/knightB.bmp",false,brd));
	brd.blackPieces.emplace(std::make_pair(6, 0), std::make_shared<Knight>(6, 0, "./Sprites/knightB.bmp",false,brd));
	//Rooks
	brd.whitePieces.emplace(std::make_pair(0, 7), std::make_shared<Rook>(0, 7, "./Sprites/rookW.bmp",true,brd));
	brd.whitePieces.emplace(std::make_pair(7, 7), std::make_shared<Rook>(7, 7, "./Sprites/rookW.bmp",true,brd));

	brd.blackPieces.emplace(std::make_pair(0, 0), std::make_shared<Rook>(0, 0, "./Sprites/rookB.bmp",false,brd));
	brd.blackPieces.emplace(std::make_pair(7, 0), std::make_shared<Rook>(7, 0, "./Sprites/rookB.bmp",false,brd));
	//Pawns
	for (int i = 0; i < 8; i++)
	{
		brd.whitePieces.emplace(std::make_pair(i,6), std::make_shared<Pawn>(i, 6, "./Sprites/pawnW.bmp",true,brd));
		brd.blackPieces.emplace(std::make_pair(i,1), std::make_shared<Pawn>(i, 1, "./Sprites/pawnB.bmp",false,brd));
	}

	gameStatus = GameState::NORMAL;
}

void Game::Update()
{
	switch(gameStatus)
	{
	case GameState::NORMAL:
		
		//Players turn and they are not promoting
		if (player.PlayerTurn() && !player.Promotion())
		{
			player.DoTurn();
		}

		//Player is promoting
		if (player.Promotion())
		{
			player.Promote(&brd.whitePieces);
		}

		//Opponents turn and not promoting
		if (!player.PlayerTurn() && !opponent.Promotion())
		{
			opponent.DoTurn();
			player.SetPlayerTurn();
		}

		//Opponent promoting
		if (opponent.Promotion())
		{
			opponent.Promote(&brd.whitePieces);
			player.SetPlayerTurn();

		}

		//End game status checks
		if (opponent.GetCheckMated())
		{
			gameStatus = GameState::OPPONENTCHECKMATED;
		}

		if (player.GetCheckMated())
		{
			gameStatus = GameState::PLAYERCHECKMATED;
		}

		if (player.GetStaleMated() || opponent.GetStaleMated())
		{
			gameStatus = GameState::STALEMATE;
		}
		break;
	}
}

void Game::Render()
{
	switch  (gameStatus)
	{
	case GameState::NORMAL:
		gui.DrawGUI(gfx);
		brd.DrawBoard(gfx);
		player.DrawPossibleMoves(gfx);
		player.DrawChecked(gfx);
		opponent.DrawChecked(gfx);
		player.DrawPieces(gfx);
		opponent.DrawPieces(gfx);
		player.DrawPromotion(gfx);
		break;
	case GameState::OPPONENTCHECKMATED:
		brd.DrawBoard(gfx);
		opponent.DrawChecked(gfx);
		player.DrawPieces(gfx);
		opponent.DrawPieces(gfx);
		gfx.DrawSprite(200, 200, playerwin);
		break;
	case GameState::PLAYERCHECKMATED:
		brd.DrawBoard(gfx);
		player.DrawChecked(gfx);
		player.DrawPieces(gfx);
		opponent.DrawPieces(gfx);
		gfx.DrawSprite(200, 200, playerlose);
		break;
	case GameState::STALEMATE:
		brd.DrawBoard(gfx);
		player.DrawPieces(gfx);
		opponent.DrawPieces(gfx);
		gfx.DrawSprite(200, 200, stalemate);
		break;
	}
}

void Game::Run()
{
	gfx.PrepareFrame();
	Update();
	Render();
	gfx.RenderFrame();
}

