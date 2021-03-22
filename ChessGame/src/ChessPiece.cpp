#include "ChessPiece.h"

ChessPiece::ChessPiece(std::string texture, int newX, int newY, SDL_Renderer* ren)
	: x(newX), y(newY), renderer(ren) {
	objTexture = TextureManager::LoadTexture(texture.c_str(), ren);

	// choose what portion of source image to take
	srcRect.h = 140;
	srcRect.w = 100;
	srcRect.x = 0;
	srcRect.y = 0;

	// put the source in destination place
	destRect.x = x + 25;  // add a little offset to x and y to center piece texture
	destRect.y = y + 11;
	destRect.w = static_cast<int>(srcRect.w * 0.7);  // 70
	destRect.h = static_cast<int>(srcRect.h * 0.7);  // 98
}

void ChessPiece::Move(const int dx, const int dy)
{
}

void ChessPiece::Render() const
{
	SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}

ChessPiece::~ChessPiece()
{
}
