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
private:
	void createPieces(std::vector<ChessPiece>& pieces, int startX, int startY, std::string prefix);
private:
	int chessBoardH, chessBoardW;
	std::vector<std::string> letters;
	std::vector<std::string> basePieces, pawns;
	std::vector<ChessPiece> whitePieces, blackPieces;
	
	SDL_Renderer* renderer;
};