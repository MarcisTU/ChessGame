#include "Game.h"

Game::Game(const char* title, int xpos, int ypos, int width, int height, bool fullScreen)
	: winHeight(height), winWidth(width)
{
	int flags = 0;
	if (fullScreen) flags = SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems initialized..." << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
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
}

void Game::Init()
{
	chessBoard = std::make_unique<ChessBoard>(ChessBoard(winHeight, winWidth, this->renderer));
	// Init Chess Board
	chessBoard->Init();
	// Init Chess Pieces
	chessPiece = std::make_unique<ChessPiece>("assets/w_queen.png", this->renderer);
}

Game::~Game()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleared!" << std::endl;
}

void Game::handleEvents()
{
	// TODO: Handle mouse events
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update()
{
	// TODO: Update board
	chessPiece->Update();
}

void Game::render()
{
	SDL_RenderClear(renderer);

	// TODO: Draw Board
	chessBoard->Draw();
	
	chessPiece->Render();
	
	SDL_RenderPresent(renderer);
}