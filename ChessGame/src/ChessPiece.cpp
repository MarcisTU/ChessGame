#include "ChessPiece.h"

ChessPiece::ChessPiece(const char* texture, SDL_Renderer* ren)
	: renderer(ren) {
	objTexture = TextureManager::LoadTexture(texture, ren);
}

void ChessPiece::Update()
{
	xpos = 0;
	ypos = 0;

	// choose what portion of source image to take
	srcRect.h = 140;
	srcRect.w = 100;
	srcRect.x = 0;
	srcRect.y = 0;

	// put the source in destination place
	destRect.x = xpos + 25;
	destRect.y = ypos + 11;
	destRect.w = static_cast<int>(srcRect.w * 0.7);
	destRect.h = static_cast<int>(srcRect.h * 0.7);
}

void ChessPiece::Move(const int dx, const int dy)
{
	
}

void ChessPiece::Render()
{
	SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}

ChessPiece::~ChessPiece()
{
	
}
