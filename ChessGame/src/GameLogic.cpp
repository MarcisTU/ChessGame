#include "pch.h"
#include "GameLogic.h"

bool GameLogic::checkIfCapturingEnemy(int curX, int curY, int color, const std::vector<ChessPiece>& chessPieces)
{
	for (const auto& piece : chessPieces)
		if (piece.GetX() == curX && piece.GetY() == curY && piece.GetColor() != color) return true;
	return false;
}

bool GameLogic::checkIfSquareHasPiece(const int curX, const int curY, const std::vector<ChessPiece>& chessPieces)
{
	for (const auto& piece : chessPieces)
		if (piece.GetX() == curX && piece.GetY() == curY) return true;
	return false;
}

void GameLogic::generateRookMoves(int curX, int curY, std::vector<std::pair<int, int>>& freeMoves, std::vector<std::pair<int, int>>& captureMoves, const std::vector<ChessPiece>& chessPieces, int color)
{
	freeMoves.clear();  // clear free moves because they might be for last chess piece
	captureMoves.clear();
	
	// Get moves in left direction
	for (int x = curX - 120; x >= 0; x -= 120)
	{
		if (checkIfSquareHasPiece(x, curY, chessPieces)) {
			if (checkIfCapturingEnemy(x, curY, color, chessPieces)) {
				captureMoves.push_back({ x, curY });
			}
			break;  // stop finding moves when reach first piece in the way
		}
		freeMoves.push_back({ x, curY });
	}

	// Get moves in upwards direction
	for (int y = curY - 120; y >= 0; y -= 120)
	{
		if (checkIfSquareHasPiece(curX, y, chessPieces)) {
			if (checkIfCapturingEnemy(curX, y, color, chessPieces))
				captureMoves.push_back({ curX, y });
			break;  // stop finding moves when reach first piece in the way
		}
		freeMoves.push_back({ curX, y });
	}

	// Get moves in right direction
	for (int x = curX + 120; x < 960; x += 120)
	{
		if (checkIfSquareHasPiece(x, curY, chessPieces)) {
			if (checkIfCapturingEnemy(x, curY, color, chessPieces))
				captureMoves.push_back({ x, curY });
			break;  // stop finding moves when reach first piece in the way
		}
		freeMoves.push_back({ x, curY });
	}

	// Get moves in downwards direction
	for (int y = curY + 120; y < 960; y += 120)
	{
		if (checkIfSquareHasPiece(curX, y, chessPieces)) {
			if (checkIfCapturingEnemy(curX, y, color, chessPieces))
				captureMoves.push_back({ curX, y });
			break;  // stop finding moves when reach first piece in the way
		}
		freeMoves.push_back({ curX, y });
	}
}

void GameLogic::generateKnightMoves(int curX, int curY, std::vector<std::pair<int, int>>& freeMoves, std::vector<std::pair<int, int>>& captureMoves, const std::vector<ChessPiece>& chessPieces, int color)
{
	int newX, newY;
	freeMoves.clear();  // clear free moves because they might be for last chess piece
	captureMoves.clear();

	std::vector<std::pair<int, int>> knightMovePos = {
		{-120, -240},  // top-left
		{120, -240},   // top-right
		{240, -120},   // right-top
		{240, 120},    // right-bottom
		{-120, 240},   // bottom-left
		{120, 240},    // bottom-right
		{-240, -120},  // left-top
		{-240, 120},   // left-bottom
	};

	for (auto& knMove : knightMovePos)
	{
		newX = curX - knMove.first;
		newY = curY - knMove.second;

		if ((newX >= 0 && newX < 960) && (newY >= 0 && newY < 960))
		{
			if (checkIfSquareHasPiece(newX, newY, chessPieces)) {// if square is taken by another piece then don't look for free move there
				if (checkIfCapturingEnemy(newX, newY, color, chessPieces))
					captureMoves.push_back({ newX, newY });
				continue;
			}
			freeMoves.push_back({ newX, newY });
		}
	}
}

void GameLogic::generateBishopMoves(int curX, int curY, std::vector<std::pair<int, int>>& freeMoves, std::vector<std::pair<int, int>>& captureMoves, const std::vector<ChessPiece>& chessPieces, int color, bool isQueen)
{
	if (!isQueen) {
		freeMoves.clear();  // clear free moves because they might be for last chess piece
		captureMoves.clear();
	}

	// Get moves in top-left direction
	for (int x = curX - 120, y = curY - 120; x >= 0 && y >= 0; x -= 120, y -= 120)
	{
		if (checkIfSquareHasPiece(x, y, chessPieces)) {
			if (checkIfCapturingEnemy(x, y, color, chessPieces))
				captureMoves.push_back({ x, y });
			break;  // stop looking for moves when reach first piece in the way
		}
		freeMoves.push_back({ x, y });
	}

	// Get moves in top-right direction
	for (int x = curX + 120, y = curY - 120; y >= 0 && x < 960; x += 120, y -= 120)
	{
		if (checkIfSquareHasPiece(x, y, chessPieces)) {
			if (checkIfCapturingEnemy(x, y, color, chessPieces))
				captureMoves.push_back({ x, y });
			break;  // stop looking for moves when reach first piece in the way
		}
		freeMoves.push_back({ x, y });
	}

	// Get moves in bottom-right direction
	for (int x = curX + 120, y = curY + 120; x < 960 && y < 960; x += 120, y += 120)
	{
		if (checkIfSquareHasPiece(x, y, chessPieces)) {
			if (checkIfCapturingEnemy(x, y, color, chessPieces))
				captureMoves.push_back({ x, y });
			break;  // stop looking for moves when reach first piece in the way
		}
		freeMoves.push_back({ x, y });
	}

	// Get moves in bottom-left direction
	for (int x = curX - 120, y = curY + 120; x >= 0 && y < 960; x -= 120, y += 120)
	{
		if (checkIfSquareHasPiece(x, y, chessPieces)) {
			if (checkIfCapturingEnemy(x, y, color, chessPieces))
				captureMoves.push_back({ x, y });
			break;  // stop looking for moves when reach first piece in the way
		}
		freeMoves.push_back({ x, y });
	}
}

void GameLogic::generateKingMoves(int curX, int curY, std::vector<std::pair<int, int>>& freeMoves, std::vector<std::pair<int, int>>& captureMoves, const std::vector<ChessPiece>& chessPieces, int color)
{
	int newX, newY;
	freeMoves.clear();  // clear free moves because they might be for last chess piece
	captureMoves.clear();
	
	std::vector<std::pair<int, int>> kingMovePos = {
		{-120, -120},  // top-left
		{0, -120},     // top
		{120, -120},   // top-right
		{120, 0},      // right
		{120, 120},    // right-bottom
		{0, 120},      // bottom
		{-120, 120},   // bottom-left
		{-120, 0},   // left
	};

	for (auto& kingMove : kingMovePos)
	{
		newX = curX - kingMove.first;
		newY = curY - kingMove.second;

		if ((newX >= 0 && newX < 960) && (newY >= 0 && newY < 960))
		{
			if (checkIfSquareHasPiece(newX, newY, chessPieces)) {
				if (checkIfCapturingEnemy(newX, newY, color, chessPieces))
					captureMoves.push_back({ newX, newY });
				continue;
			}
			freeMoves.push_back({ newX, newY });
		}
	}
}

void GameLogic::generateBlackPawnMoves(int curX, int curY, std::vector<std::pair<int, int>>& freeMoves, std::vector<std::pair<int, int>>& captureMoves, const std::vector<ChessPiece>& chessPieces, bool isFirstMove, int color)
{
	// ***** Get free moves ***** //
	freeMoves.clear();  // clear free moves because they might be for last chess piece
	captureMoves.clear();

	if (!checkIfSquareHasPiece(curX, curY - 120, chessPieces)) {
		freeMoves.push_back({ curX, curY - 120 });
		if (!checkIfSquareHasPiece(curX, curY - 240, chessPieces) && isFirstMove)
			freeMoves.push_back({ curX, curY - 240 });
	}

	// ***** Get capture moves ***** //
	// - Check left diagonal capture move
	if ((curX > 0 && curY > 0)
		&& checkIfSquareHasPiece(curX - 120, curY - 120, chessPieces)
		&& checkIfCapturingEnemy(curX - 120, curY - 120, color, chessPieces))
		captureMoves.push_back({ curX - 120, curY - 120 });

	// - Check right diagonal capture move
	if ((curX < 840 && curY > 0)
		&& checkIfSquareHasPiece(curX + 120, curY - 120, chessPieces)
		&& checkIfCapturingEnemy(curX + 120, curY - 120, color, chessPieces))
		captureMoves.push_back({ curX + 120, curY - 120 });
}

void GameLogic::generateWhitePawnMoves(int curX, int curY, std::vector<std::pair<int, int>>& freeMoves, std::vector<std::pair<int, int>>& captureMoves, const std::vector<ChessPiece>& chessPieces, bool isFirstMove, int color)
{
	// ***** Get free moves ***** //
	freeMoves.clear();  // clear free moves because they might be for last chess piece
	captureMoves.clear();

	if (!checkIfSquareHasPiece(curX, curY + 120, chessPieces)) {
		freeMoves.push_back({ curX, curY + 120 });
		if (!checkIfSquareHasPiece(curX, curY + 240, chessPieces) && isFirstMove) 
			freeMoves.push_back({ curX, curY + 240 });
	}

	// ***** Get capture moves ***** //
	// - Check left diagonal capture move
	if ((curX > 0 && curY < 840)
		&& checkIfSquareHasPiece(curX - 120, curY + 120, chessPieces)
		&& checkIfCapturingEnemy(curX - 120, curY + 120, color, chessPieces))
		captureMoves.push_back({ curX - 120, curY + 120 });

	// - Check right diagonal capture move
	if ((curX < 840 && curY < 840)
		&& checkIfSquareHasPiece(curX + 120, curY + 120, chessPieces)
		&& checkIfCapturingEnemy(curX + 120, curY + 120, color, chessPieces))
		captureMoves.push_back({ curX + 120, curY + 120 });
}