#include "Game.h"


/*
BUG LIST
.played moves overwrites after a while
TODO LIST
.Generational Minimax AI
.Player best move
.GUI stuff
.Multiplayer Promotion
*/

Game::Game(Window & wnd)
	:
	wnd(wnd),
	gfx(wnd.GetHandle()),
	brd("./Sprites/board.bmp",30,25),
	gui(brd),
	playerwin("./Sprites/checkmatepwin.bmp"),
	playerlose("./Sprites/checkmateplose.bmp"),
	stalemate("./Sprites/stalemate.bmp"),
	draw("./Sprites/draw.bmp"),
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

	engine = irrklang::createIrrKlangDevice();
}

void Game::Update()
{
	switch (programStatus)
	{
	case MAINMENU:
		menu.UpdateMenu(wnd, engine);
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
					//If we're checked and can play the sound then play it
					if (blackPlayer.GetChecked() && checkSound)
					{
						engine->play2D("./Sounds/check.wav", false);
						checkSound = false;
					}
					//If we're not checked and the sound can't be played then reset it
					else if (!blackPlayer.GetChecked() && !checkSound)
					{
						checkSound = true;
					}
					blackPlayer.DoTurn();
					engine->play2D("./Sounds/piecemove.wav", false);
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
					//If we're checked and can play the sound then play it
					if (whitePlayer.GetChecked() && checkSound)
					{
						engine->play2D("./Sounds/check.wav", false);
						checkSound = false;
					}
					//If we're not checked and the sound can't be played then reset it
					else if (!whitePlayer.GetChecked() && !checkSound)
					{
						checkSound = true;
					}
					whitePlayer.DoTurn();
					if (!whitePlayer.PlayerTurn())
					{
						engine->play2D("./Sounds/piecemove.wav", false);
					}
				}

				//Player is promoting
				if (whitePlayer.GetPromotion())
				{
					whitePlayer.Promote(&brd.whitePieces);
				}

				//End game status checks 
				//Checkmate
				if (blackPlayer.GetCheckMated())
				{
					gameStatus = GameState::OPPONENTCHECKMATED;
					if (checkmateSound)
					{
						engine->play2D("./Sounds/checkmate.wav", false);
						checkmateSound = false;
					}					
				}

				if (whitePlayer.GetCheckMated())
				{
					gameStatus = GameState::PLAYERCHECKMATED;
					if (checkmateSound)
					{
						engine->play2D("./Sounds/checkmate.wav", false);
						checkmateSound = false;
					}
				}
				//Stalemate checks
				if (whitePlayer.GetStaleMated() || blackPlayer.GetStaleMated())
				{
					gameStatus = GameState::STALEMATE;
					if (staleSound)
					{
						engine->play2D("./Sounds/stalemate.wav", false);
						staleSound = false;
					}
				}
				//Draw
				if (whitePlayer.TestForDraw() || blackPlayer.TestForDraw())
				{
					gameStatus = GameState::DRAW;

					if (drawSound)
					{
						engine->play2D("./Sounds/draw.wav", false);
						drawSound = false;
					}
				}
			}
			else
			//do a multiplayer loop
			{
				if (isServer)
				{
					//If we're the server constantly check for packets.
					server.ReceivePacket();

					if (server.GetServerStatus() == 3)
					{
						programStatus = ProgramState::MAINMENU;
						isMultiplayer = false;
						isClient = false;
					}

					if (server.CheckNewMessage())
					{
						blackPlayer.DoMPlayUpdate(server.GetLatestMove());
						server.SetNewMessage(false);
						whitePlayer.SetPlayerTurn(true);
					}

					//Handle the logic for sending packets.
					if (whitePlayer.PlayerTurn())
					{
						whitePlayer.TestForCheck();
						//If we're checked and can play the sound then play it
						if (whitePlayer.GetChecked() && checkSound)
						{
							engine->play2D("./Sounds/check.wav", false);
							checkSound = false;
						}
						//If we're not checked and the sound can't be played then reset it
						else if (!whitePlayer.GetChecked() && !checkSound)
						{
							checkSound = true;
						}
						whitePlayer.DoTurn();
						if (whitePlayer.PacketReady())
						{
							std::string data;
							data = std::to_string(brd.playedMoves.back().first.x) +
								std::to_string(brd.playedMoves.back().first.y) +
								std::to_string(brd.playedMoves.back().second.x) +
								std::to_string(brd.playedMoves.back().second.y);
							server.SendPacket(data);
							whitePlayer.SetPacketNotReady();
							blackPlayer.SetPlayerTurn(true);
						}

						//Endgame states
						if (blackPlayer.GetCheckMated())
						{
							gameStatus = GameState::OPPONENTCHECKMATED;
							if (checkmateSound)
							{
								engine->play2D("./Sounds/checkmate.wav", false);
								checkmateSound = false;
							}
						}

						if (whitePlayer.GetCheckMated())
						{
							gameStatus = GameState::PLAYERCHECKMATED;
							if (checkmateSound)
							{
								engine->play2D("./Sounds/checkmate.wav", false);
								checkmateSound = false;
							}
						}
						//Stalemate checks
						if (whitePlayer.GetStaleMated() || blackPlayer.GetStaleMated())
						{
							gameStatus = GameState::STALEMATE;
							if (staleSound)
							{
								engine->play2D("./Sounds/stalemate.wav", false);
								staleSound = false;
							}
						}
						//Draw
						if (whitePlayer.TestForDraw() || blackPlayer.TestForDraw())
						{
							gameStatus = GameState::DRAW;

							if (drawSound)
							{
								engine->play2D("./Sounds/draw.wav", false);
								drawSound = false;
							}
						}
					}
				}
				if (isClient)
				{
					//If we're client then constantly check for packets
					client.ReceivePacket();

					//If packet contains disconnect message from server
					if (client.GetStatus() == 3)
					{
						programStatus = ProgramState::MAINMENU;
						isMultiplayer = false;
						isClient = false;
					}

					//Read the message and update the white player from the data
					//Nothing new to read, set client turn
					if (client.CheckNewMessage())
					{
						whitePlayer.DoMPlayUpdate(client.GetLatestMove());
						client.SetNewMessage(false);
					    blackPlayer.SetPlayerTurn(true);
					}

					if (blackPlayer.PlayerTurn())
					{
						blackPlayer.TestForCheck();
						//If we're checked and can play the sound then play it
						if (blackPlayer.GetChecked() && checkSound)
						{
							engine->play2D("./Sounds/check.wav", false);
							checkSound = false;
						}
						//If we're not checked and the sound can't be played then reset it
						else if (!blackPlayer.GetChecked() && !checkSound)
						{
							checkSound = true;
						}
						blackPlayer.mDoTurn();
						if (blackPlayer.PacketReady())
						{
							std::string data;
							data = std::to_string(brd.playedMoves.back().first.x) +
								std::to_string(brd.playedMoves.back().first.y) +
								std::to_string(brd.playedMoves.back().second.x) +
								std::to_string(brd.playedMoves.back().second.y);
							client.SendPacket(data);
							blackPlayer.SetPacketNotReady();
							whitePlayer.SetPlayerTurn(true);
						}
						if (whitePlayer.GetCheckMated())
						{
							gameStatus = GameState::OPPONENTCHECKMATED;
							if (checkmateSound)
							{
								engine->play2D("./Sounds/checkmate.wav", false);
								checkmateSound = false;
							}
						}

						if (blackPlayer.GetCheckMated())
						{
							gameStatus = GameState::PLAYERCHECKMATED;
							if (checkmateSound)
							{
								engine->play2D("./Sounds/checkmate.wav", false);
								checkmateSound = false;
							}
						}
						//Stalemate checks
						if (whitePlayer.GetStaleMated() || blackPlayer.GetStaleMated())
						{
							gameStatus = GameState::STALEMATE;
							if (staleSound)
							{
								engine->play2D("./Sounds/stalemate.wav", false);
								staleSound = false;
							}
						}
						//Draw
						if (whitePlayer.TestForDraw() || blackPlayer.TestForDraw())
						{
							gameStatus = GameState::DRAW;

							if (drawSound)
							{
								engine->play2D("./Sounds/draw.wav", false);
								drawSound = false;
							}
						}
					}
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
			case 3:
				programStatus = ProgramState::MAINMENU;
				isMultiplayer = false;
				isClient = false;
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
			case 3:
				programStatus = ProgramState::MAINMENU;
				isMultiplayer = false;
				isServer = false;
				break;
		}
		break;
	case QUIT:
		engine->drop();
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
			if (isClient)
			{
				blackPlayer.DrawPossibleMoves(gfx);
			}
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
		case GameState::DRAW:
			brd.DrawBoard(gfx);
			whitePlayer.DrawPieces(gfx);
			blackPlayer.DrawPieces(gfx);
			gfx.DrawSprite(200, 200, draw);
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

