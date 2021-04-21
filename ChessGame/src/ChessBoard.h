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
	void MovePiece(int deltaX, int deltaY) const;
	void drawAvailableMoves() const;
	void getCurPieceMoves(const ChessPiece* curChessPiece);
private:
	void createPieces(std::vector<ChessPiece>& pieces, int startX, int startY, std::string_view prefix);
	int findPieceId(std::string_view& name);
	ChessPiece removeCaptured(int x, int y);
	bool isKingChecked(int color);
private:
	bool kingCheck = false;
	int chessBoardH = 0, chessBoardW = 0;
	enum chessPieceColor { WHITE, BLACK };
	enum chessPieceID { ROOK, KNIGHT, BISHOP, KING, QUEEN, PAWN };
	//const char letters[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
	std::vector<ChessPiece> chessPieces;
	std::vector<ChessPiece> capturedPieces;
	std::vector<std::pair<int, int>> freeMoves;
	std::vector<std::pair<int, int>> captureMoves;
	
	SDL_Renderer* renderer;
	ChessPiece* curChessPiece;
	GameLogic engine;
};