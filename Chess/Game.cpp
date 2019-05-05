#include "Game.h"


/*
BUG LIST
TODO LIST
.Drawn games
.Generational Minimax AI
.Player best move
.Sounds
.Multiplayer
*/

Game::Game(Window & wnd)
	:
	wnd(wnd),
	gfx(wnd.GetHandle()),
	brd("./Sprites/board.bmp",30,25),
	gui(brd),
	whitePlayer(wnd,brd,gui),
	blackPlayer(wnd,brd),
	menu(),
	server(),
	client()
{
	//Kings
	brd.whitePieces.emplace(std::make_pair(3, 7), std::make_shared<King>(3, 7, "./Sprites/kingW.bmp",true,brd));
	brd.blackPieces.emplace(std::make_pair(3, 0), std::make_shared<King>(3, 0, "./Sprites/kingB.bmp",false,brd));
	//Queens
	brd.whitePieces.emplace(std::make_pair(4,7), std::make_shared<Queen>(4, 7, "./Sprites/queenW.bmp",true,brd));
	brd.blackPieces.emplace(std::make_pair(4,0), std::make_shared<Queen>(4, 0, "./Sprites/queenB.bmp",false,brd));
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
	programStatus = ProgramState::MAINMENU;
	gameStatus = GameState::NORMAL;
}

void Game::Update()
{
	switch (programStatus)
	{
	case MAINMENU:
		menu.UpdateMenu(wnd);
		if (wnd.inpt.LeftMsePressed())
		{
			programStatus += menu.GetSelectedState();
		}
		break;
	case PLAYING:
		switch (gameStatus)
		{
		case GameState::NORMAL:
			if (!isMultiplayer)
			{
				//Opponents turn and not promoting
				if (!whitePlayer.PlayerTurn() && !blackPlayer.GetPromotion())
				{
					blackPlayer.TestForCheck();
					blackPlayer.DoTurn();
					whitePlayer.SetPlayerTurn(true);
				}

				//Opponent promoting
				if (blackPlayer.GetPromotion())
				{
					blackPlayer.Promote(&brd.blackPieces);
					whitePlayer.SetPlayerTurn(true);

				}

				//Players turn and they are not promoting
				if (whitePlayer.PlayerTurn() && !whitePlayer.GetPromotion())
				{
					whitePlayer.TestForCheck();
					whitePlayer.DoTurn();
				}

				//Player is promoting
				if (whitePlayer.GetPromotion())
				{
					whitePlayer.Promote(&brd.whitePieces);
				}

				//End game status checks
				if (blackPlayer.GetCheckMated())
				{
					gameStatus = GameState::OPPONENTCHECKMATED;
				}

				if (whitePlayer.GetCheckMated())
				{
					gameStatus = GameState::PLAYERCHECKMATED;
				}

				if (whitePlayer.GetStaleMated() || blackPlayer.GetStaleMated())
				{
					gameStatus = GameState::STALEMATE;
				}
			}
			else
			//do a multiplayer loop
			{
				if (isServer)
				{
					//If we're the server constantly check for packets.
					server.ReceivePacket();
					//Handle the logic for sending packets.
					if (whitePlayer.PlayerTurn())
					{
						whitePlayer.DoTurn();
						if (brd.playedMoves.size() > 0)
						{
							std::string data;
							data = std::to_string(brd.playedMoves.back().first.x) +
								std::to_string(brd.playedMoves.back().first.y) +
								std::to_string(brd.playedMoves.back().second.x) +
								std::to_string(brd.playedMoves.back().second.y);
							server.SendPacket(data);
						}
					}
				}
				if (isClient)
				{
				//If we're client then constantly check for packets
				client.ReceivePacket();
				/*
				if (blackPlayer.PlayerTurn())
				{
					blackPlayer.DoTurn();
					if (brd.playedMoves.size() > 0)
					{
						std::string data;
						data = std::to_string(brd.playedMoves.back().first.x) +
							std::to_string(brd.playedMoves.back().first.y) +
							std::to_string(brd.playedMoves.back().second.x) +
							std::to_string(brd.playedMoves.back().second.y);
						server.SendPacket(data);
					}
				}*/
				
				}

			}
			break;
		}
		break;
	case JOINING:
		if (wnd.inpt.KbdKeyPressed(VK_SPACE))
		{
			programStatus = ProgramState::MAINMENU;
		}
		switch(client.GetStatus())
		{
			case 0:
				client.JoinGame();
				break;
			case 1:
				break;
			case 2:
				programStatus = ProgramState::PLAYING;
				isMultiplayer = true;
				isClient = true;
				break;
		}
		break;
	case HOSTING:
		if (wnd.inpt.KbdKeyPressed(VK_SPACE))
		{
			server.Cleanup();
			programStatus = ProgramState::MAINMENU;
		}
		switch (server.GetServerStatus())
		{
			case 0:
				server.CreateServer();
				break;
			case 1:
				server.WaitForConnections();
				break;
			case 2:
				programStatus = ProgramState::PLAYING;
				isMultiplayer = true;
				isServer = true;
				break;
		}
		break;
	case QUIT:
		PostQuitMessage(0);
		break;
	}
}

void Game::Render()
{
	switch (programStatus)
	{
	case MAINMENU:
		menu.DrawMenuScreen(gfx);
		break;
	case PLAYING:
		switch (gameStatus)
		{
		case GameState::NORMAL:
			gui.DrawGUI(gfx);
			brd.DrawBoard(gfx);
			whitePlayer.DrawPossibleMoves(gfx);
			whitePlayer.DrawChecked(gfx);
			blackPlayer.DrawChecked(gfx);
			whitePlayer.DrawPieces(gfx);
			blackPlayer.DrawPieces(gfx);
			if (whitePlayer.GetPromotion())
			{
				gui.DrawPromotion(gfx);
			}
			break;
		case GameState::OPPONENTCHECKMATED:
			brd.DrawBoard(gfx);
			blackPlayer.DrawChecked(gfx);
			whitePlayer.DrawPieces(gfx);
			blackPlayer.DrawPieces(gfx);
			gfx.DrawSprite(200, 200, playerwin);
			break;
		case GameState::PLAYERCHECKMATED:
			brd.DrawBoard(gfx);
			whitePlayer.DrawChecked(gfx);
			whitePlayer.DrawPieces(gfx);
			blackPlayer.DrawPieces(gfx);
			gfx.DrawSprite(200, 200, playerlose);
			break;
		case GameState::STALEMATE:
			brd.DrawBoard(gfx);
			whitePlayer.DrawPieces(gfx);
			blackPlayer.DrawPieces(gfx);
			gfx.DrawSprite(200, 200, stalemate);
			break;
		}
		break;
	case HOSTING:
		server.DrawStates(gfx);
		break;
	case JOINING:
		client.DrawStates(gfx);
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

