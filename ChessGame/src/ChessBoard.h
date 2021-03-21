#pragma once
#include <string>
#include <vector>

#include "SDL2/SDL.h"

class ChessBoard
{
public:
	ChessBoard(int winHeight, int winWidth, SDL_Renderer* ren);
	~ChessBoard();
	
	void Init();
	void Draw();
private:
	int chessBoardH, chessBoardW;
	std::vector<std::string> letters;
	SDL_Rect chessTile;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer;
};