#pragma once
#include "SDL2/SDL.h"
#include <iostream>

#include "ChessPiece.h"
#include "ChessBoard.h"

class Game
{
public:
	Game(const char* title, int xpos, int ypos, int width, int height, bool fullScreen);
	~Game();

	void Init();
	
	void handleEvents();
	void update();
	void render();

	inline bool running() { return isRunning; }
private:
	int winHeight, winWidth;
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::unique_ptr<ChessPiece> chessPiece;
	std::unique_ptr<ChessBoard> chessBoard;
};