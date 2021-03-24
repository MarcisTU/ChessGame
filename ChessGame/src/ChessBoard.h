#pragma once
#include <string>
#include <vector>

#include "ChessPiece.h"
#include "SDL2/SDL.h"

class ChessBoard
{
public:
	ChessBoard() = default;
	ChessBoard(int winHeight, int winWidth, SDL_Renderer* ren);
	~ChessBoard();
	
	void Init() const;
	void InitPieces();
	void Draw() const;
	void RenderPieces();
	void UpdateMovedPos();
	void getClicked(int mouseX, int mouseY);
	void MovePiece(int deltaX, int deltaY);
private:
	void createPieces(std::vector<ChessPiece>& pieces, int startX, int startY, std::string_view prefix);
private:
	int chessBoardH, chessBoardW;
	std::vector<std::string_view> letters;
	std::vector<std::string_view> basePieces, pawns;
	std::vector<ChessPiece> chessPieces;

	ChessPiece* curChessPiece;
	SDL_Renderer* renderer;
};