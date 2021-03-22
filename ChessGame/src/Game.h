#pragma once
#include "SDL2/SDL.h"

#include "ChessBoard.h"

class Game
{
public:
	Game(std::string title, int xpos, int ypos, int width, int height);
	~Game();

	void Init();
	
	void handleEvents();
	void update();
	void render();

	bool running() { return isRunning; }
private:
	int winHeight, winWidth;
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
	
	ChessBoard chessBoard;
};