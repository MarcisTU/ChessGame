#pragma once
#include <iostream>

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
	bool isRunning, leftMouseBtnDown;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Point mousePos, lastMousePos;
	ChessBoard chessBoard;
};