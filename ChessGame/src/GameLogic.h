#pragma once
#include "pch.h"

#include "ChessPiece.h"

class GameLogic
{
public:
	GameLogic() = default;
	GameLogic(SDL_Renderer* rend);
	
	bool checkIfCapturingEnemy(int curX, int curY, int color, const std::vector<ChessPiece>& chessPieces);
	bool checkIfSquareHasPiece(int curX, int curY, const std::vector<ChessPiece>& chessPieces);
	void generateRookMoves(int curX, int curY, std::vector<std::pair<int, int>>& freeMoves, const std::vector<ChessPiece>& chessPieces);
	void generateKnightMoves(int curX, int curY, std::vector<std::pair<int, int>>& freeMoves, const std::vector<ChessPiece>& chessPieces);
	void generateBishopMoves(int curX, int curY, std::vector<std::pair<int, int>>& freeMoves, const std::vector<ChessPiece>& chessPieces, bool isQueen = false);
	void generateKingMoves(int curX, int curY, std::vector<std::pair<int, int>>& freeMoves, const std::vector<ChessPiece>& chessPieces);
	void generateBlackPawnMoves(int curX, int curY, std::vector<std::pair<int, int>>& freeMoves, std::vector<std::pair<int, int>>& captureMoves, const std::vector<ChessPiece>& chessPieces, bool isFirstMove, int color);
	void generateWhitePawnMoves(int curX, int curY, std::vector<std::pair<int, int>>& freeMoves, std::vector<std::pair<int, int>>& captureMoves, const std::vector<ChessPiece>& chessPiece, bool isFirstMove, int color);
private:
	SDL_Renderer* renderer;
};

