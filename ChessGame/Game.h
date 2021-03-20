#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include "ChessPiece.h"

class Game
{
public:
	Game(const char* title, int xpos, int ypos, int width, int height, bool fullScreen);
	~Game();

	void handleEvents();
	void update();
	void render();

	inline bool running() { return isRunning; }
private:
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
	ChessPiece* chessPiece;
};