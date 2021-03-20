#pragma once
#include "SDL2/SDL.h"
#include "TextureManager.h"

class ChessPiece
{
public:
	ChessPiece(const char* texture, SDL_Renderer* renderer);
	~ChessPiece();

	void Update();
	void Render();
	void Move(int dx, int dy);
private:
	int xpos, ypos;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer;
};
