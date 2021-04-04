#pragma once
#include "pch.h"

#include "TextureManager.h"

class ChessPiece
{
public:
	ChessPiece() = default;
	ChessPiece(const std::string& texture, int newX, int newY, SDL_Renderer* renderer, int pieceId, int pieceColor);

	void Render() const;
	void Move(int dx, int dy);
	int GetX() const { return x; }
	int GetY() const { return y; }
	int GetID() const { return id; }
	int GetColor() const { return color; }
	int GetDestX() const { return destRect.x; }
	int GetDestY() const { return destRect.y; }
	void ResetPos();
	void setPos(int newX, int newY);
	bool firstmove() const { return firstMoveOfGame; }
	void setFirstMove(bool moved) { firstMoveOfGame = moved; }
	private:
	bool firstMoveOfGame = true;
	int resetX, resetY, x, y, id, color;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer;
};
