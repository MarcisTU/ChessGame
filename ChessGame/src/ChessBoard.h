#pragma once

#include "ChessPiece.h"
#include "GameLogic.h"

class ChessBoard
{
public:
	ChessBoard() = default;
	ChessBoard(int winHeight, int winWidth, SDL_Renderer* ren);
	
	void InitPieces();
	void Draw() const;
	void RenderPieces();
	void UpdateMovedPos(int mouseX, int mouseY, bool &isWhiteMove);
	void getClicked(int mouseX, int mouseY, int &curPieceColor);
	void MovePiece(int deltaX, int deltaY);
	void showCurPieceMoves();
private:
	void createPieces(std::vector<ChessPiece>& pieces, int startX, int startY, std::string_view prefix);
	int findPieceId(std::string_view& name);
	void removeCaptured(int x, int y);
private:
	int chessBoardH = 0, chessBoardW = 0;
	enum chessPieceColor { WHITE, BLACK };
	enum chessPieceID { ROOK, KNIGHT, BISHOP, KING, QUEEN, PAWN };
	//const char letters[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
	std::vector<ChessPiece> chessPieces;
	std::vector<std::pair<int, int>> freeMoves;
	std::vector<std::pair<int, int>> captureMoves;

	ChessPiece* curChessPiece;
	GameLogic engine;
	SDL_Renderer* renderer;
};