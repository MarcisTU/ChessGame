#include "Game.h"

Game::Game(std::string title, int xpos, int ypos, int width, int height)
	: winHeight(height), winWidth(width)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems initialized..." << std::endl;

		window = SDL_CreateWindow(title.c_str(), xpos, ypos, width, height, 0);
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
	// Init Chess Board
	chessBoard.Init();
	// Init Chess Pieces
	chessBoard.InitPieces();
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
}

void Game::render()
{
	SDL_RenderClear(renderer);

	chessBoard.Draw();
	
	// Render pieces
	chessBoard.RenderPieces();
	
	SDL_RenderPresent(renderer);
}