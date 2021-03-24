#pragma once

#include <iostream>
#include <string_view>

#include "SDL2/SDL.h"
#include "TextureManager.h"

class ChessPiece
{
public:
	ChessPiece() = default;
	ChessPiece(const std::string& texture, int newX, int newY, SDL_Renderer* renderer);
	~ChessPiece();

	void Render() const;
	void Move(int dx, int dy);
	int GetX() const { return x; }
	int GetY() const { return y; }
	int GetDestX() const { return destRect.x; }
	int GetDestY() const { return destRect.y; }
	void ResetPos();
private:
	int resetX, resetY, x, y;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer;
};
