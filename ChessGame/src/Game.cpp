#include "pch.h"
#include "Game.h"

Game::Game(const std::string& title, const int xPos, const int yPos, int width, int height)
	: winHeight(height), winWidth(width), leftMouseBtnDown(false), renderer(nullptr), mousePos({ 0, 0 }), lastMousePos({0, 0})
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems initialized..." << std::endl;

		window = SDL_CreateWindow(title.c_str(), xPos, yPos, width, height, 0);
		if (window) std::cout << "Window created!" << std::endl;

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 125, 200, 255, 255);
			std::cout << "Renderer created!" << std::endl;
		}

		isRunning = true; 
	}
	else isRunning = false;
	chessBoard = ChessBoard(winHeight, winWidth, renderer);
}

void Game::Init()
{
	chessBoard.Draw();
	chessBoard.InitPieces();
}

Game::~Game()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_MOUSEMOTION:
		mousePos = { event.motion.x, event.motion.y };
		break;
	case SDL_MOUSEBUTTONUP:
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			leftMouseBtnDown = false;
			// Only try to update moved piece position if actual piece was selected
			if (curPieceColor == 0 && isWhiteMove || curPieceColor == 1 && !isWhiteMove)
				chessBoard.UpdateMovedPos(mousePos.x, mousePos.y, isWhiteMove);
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			leftMouseBtnDown = true;
			chessBoard.getClicked(mousePos.x, mousePos.y, curPieceColor);
			chessBoard.getCurPieceMoves();
		}
		break;
	default:
		break;
	}
}

void Game::update()
{
	// Check if it's white or black move and if according piece color is selected
	if (leftMouseBtnDown && (curPieceColor == 0 && isWhiteMove || curPieceColor == 1 && !isWhiteMove))
	{
		// Create draggable object effect while mouse button is pressed on chess piece and moved around
		chessBoard.MovePiece((mousePos.x - lastMousePos.x), (mousePos.y - lastMousePos.y));
	}
	lastMousePos = mousePos;
}

void Game::render()
{
	SDL_RenderClear(renderer);

	chessBoard.Draw();

	if (leftMouseBtnDown && (curPieceColor == 0 && isWhiteMove || curPieceColor == 1 && !isWhiteMove)) // render chess piece move placeholders if any piece is selected
		chessBoard.drawAvailableMoves();
	
	chessBoard.RenderPieces();
	
	SDL_RenderPresent(renderer);
}