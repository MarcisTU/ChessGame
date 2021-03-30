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
	void UpdateMovedPos(int mouseX, int mouseY);
	void getClicked(int mouseX, int mouseY);
	void MovePiece(int deltaX, int deltaY);
	void showCurPieceMoves();
private:
	void createPieces(std::vector<ChessPiece>& pieces, int startX, int startY, std::string_view prefix);
	int findPieceId(std::string_view& name);
	// TODO Free move generation functions
	void generateBlackPawnMoves();
	void generateWhitePawnMoves();
	void generateRookMoves();
	void generateKnightMoves();
	void generateBishopMoves();
	void generateKingMoves();
	void generateQueenMoves();
	bool checkIfSquareHasPiece(int curX, int curY);
private:
	enum chessPieceID { ROOK, KNIGHT, BISHOP, KING, QUEEN, W_PAWN, B_PAWN };
	int chessBoardH, chessBoardW;
	std::vector<std::string_view> letters;
	std::vector<ChessPiece> chessPieces;
	std::vector<std::pair<int, int>> freeMoves;

	ChessPiece* curChessPiece;
	SDL_Renderer* renderer;
};