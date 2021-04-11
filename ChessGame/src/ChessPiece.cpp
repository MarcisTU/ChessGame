#include "pch.h"
#include "ChessPiece.h"

ChessPiece::ChessPiece(const std::string& texture, int newX, int newY, SDL_Renderer* ren, int pieceId, int pieceColor)
	: x(newX), y(newY), id(pieceId), color(pieceColor), renderer(ren), srcRect({0, 0, 0, 0}), destRect({0, 0, 0, 0})
{
	objTexture = TextureManager::LoadTexture(texture.c_str(), ren);

	// choose what portion of source image to take
	srcRect.h = 140;
	srcRect.w = 100;
	srcRect.x = 0;
	srcRect.y = 0;

	// set initial "home" coordinates for piece
	resetX = x + 25;
	resetY = y + 11;
	
	// put the source in destination place
	destRect.x = x + 25;  // add a little offset to x and y to center piece texture
	destRect.y = y + 11;
	destRect.w = static_cast<int>(srcRect.w * 0.7);  // 70
	destRect.h = static_cast<int>(srcRect.h * 0.7);  // 98
}

void ChessPiece::Move(int dx, int dy)
{
	destRect.x += dx;
	destRect.y += dy;
}

void ChessPiece::ResetPos()
{
	destRect.x = resetX;
	destRect.y = resetY;
}

void ChessPiece::setPos(const int newX, const int newY, int offsetX, int offsetY)
{
	x = newX;
	y = newY;
	resetX = x + offsetX;
	resetY = y + offsetY;
	destRect.x = x + offsetX;
	destRect.y = y + offsetY;
}

void ChessPiece::setDimensions(int width, int height)
{
	destRect.w = width;
	destRect.h = height;
}

void ChessPiece::Render() const
{
	SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}