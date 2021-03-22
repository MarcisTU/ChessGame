#pragma once

#include <iostream>

#include "SDL2/SDL.h"
#include "TextureManager.h"

class ChessPiece
{
public:
	ChessPiece(std::string texture, int newX, int newY, SDL_Renderer* renderer);
	~ChessPiece();

	void Render() const;
	void Move(int dx, int dy);
private:
	int x, y;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer;
};
