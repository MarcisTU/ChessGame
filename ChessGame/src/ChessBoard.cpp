#include "ChessBoard.h"

ChessBoard::ChessBoard(int winHeight, int winWidth, SDL_Renderer* ren)
	: chessBoardH(winHeight), chessBoardW(winWidth), renderer(ren)
{
	letters = { "a", "b", "c", "d", "e", "f", "g", "h" }; // will use this later for notation
	curChessPiece = nullptr;
}

void ChessBoard::Draw() const
{
	SDL_Rect chessTile;
	
	for (int row = 0; row < chessBoardH; row+=120)
	{
		for (int col = 0; col < chessBoardW; col+=120)
		{
			chessTile.x = col;
			chessTile.y = row;
			chessTile.w = 120;
			chessTile.h = 120;

			const int curColNum = col / 120;
			const int curRowNum = row / 120;
			
			if ((curColNum % 2 == 0 && curRowNum % 2 == 0) 
				|| (curColNum % 2 != 0 && curRowNum % 2 != 0))
			{
				// Set render color to White
				SDL_SetRenderDrawColor(renderer, 230, 230, 230, 255);

				// Render rect
				SDL_RenderFillRect(renderer, &chessTile);
			} else
			{
				// Set render color to Black
				SDL_SetRenderDrawColor(renderer, 31, 48, 74, 255);

				// Render rect
				SDL_RenderFillRect(renderer, &chessTile);
			}
		}
	}
}

void ChessBoard::RenderPieces()
{
	for (auto& it : chessPieces)
	{
		// filter for current selected piece
		if (curChessPiece != nullptr)
		{
			if ((it.GetX() == curChessPiece->GetX()) && (it.GetY() == curChessPiece->GetY()))
			{
				// skip rendering of current selected chess piece, because
				// we want it to appear on top of everyone else
				continue;
			}
		}
		it.Render();
	}
	// finally if there was a chess piece selected then render it last
	if (curChessPiece != nullptr)
	{
		curChessPiece->Render();
	}
}

void ChessBoard::getClicked(int mouseX, int mouseY)
{
	int pieceX, pieceY;
	for (auto& piece : chessPieces)
	{
		pieceX = piece.GetX();
		pieceY = piece.GetY();
		if ((mouseX >= pieceX && mouseX < (pieceX + 120)) 
			&& (mouseY >= pieceY && mouseY < (pieceY + 120)))
		{
			curChessPiece = &piece;
		}
	}
}

void ChessBoard::showCurPieceMoves()
{
	if (curChessPiece != nullptr)
		switch(curChessPiece->GetID())
		{
		case B_PAWN:
			generateBlackPawnMoves();
			break;
		case W_PAWN:
			generateWhitePawnMoves();
			break;
		case ROOK:
			generateRookMoves();
			break;
		case KNIGHT:
			generateKnightMoves();
			break;
		case BISHOP:
			generateBishopMoves();
			break;
		case KING:
			generateKingMoves();
			break;
		case QUEEN:
			generateQueenMoves();
			break;
		default:
			break;
		}
}

bool ChessBoard::checkIfSquareHasPiece(const int curX, const int curY)
{
	for (auto& piece : chessPieces)
		if (piece.GetX() == curX && piece.GetY() == curY) return true;
	return false;
}

void ChessBoard::generateQueenMoves()
{
	// Generate vertical and horizontal moves
	generateRookMoves();

	// Diagonal moves
	generateBishopMoves();
}

void ChessBoard::generateRookMoves()
{
	SDL_Rect r;
	r.h = 60;
	r.w = 60;
	int curX = curChessPiece->GetX();
	int curY = curChessPiece->GetY();
	freeMoves.clear();  // clear free moves because they might be for last chess piece
	
	// Draw moves in left direction
	for (int x = curX - 120; x >= 0; x -= 120)
	{
		if (checkIfSquareHasPiece(x, curY)) break;  // stop showing moves when reach first piece in the way
		SDL_SetRenderDrawColor(renderer, 79, 55, 158, 90);
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

		r.x = x + 30;
		r.y = curY + 30;
		SDL_RenderFillRect(renderer, &r);
		freeMoves.push_back({x, curY});
	}

	// Draw moves in upwards direction
	for (int y = curY - 120; y >= 0; y -= 120)
	{
		if (checkIfSquareHasPiece(curX, y)) break;  // stop showing moves when reach first piece in the way
		SDL_SetRenderDrawColor(renderer, 79, 55, 158, 90);
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

		r.x = curX + 30;
		r.y = y + 30;
		SDL_RenderFillRect(renderer, &r);
		freeMoves.push_back({ curX, y });
	}

	// Draw moves in right direction
	for (int x = curX + 120; x < 960; x += 120)
	{
		if (checkIfSquareHasPiece(x, curY)) break;  // stop showing moves when reach first piece in the way
		SDL_SetRenderDrawColor(renderer, 79, 55, 158, 90);
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

		r.x = x + 30;
		r.y = curY + 30;
		SDL_RenderFillRect(renderer, &r);
		freeMoves.push_back({ x, curY });
	}

	// Draw moves in downwards direction
	for (int y = curY + 120; y < 960; y += 120)
	{
		if (checkIfSquareHasPiece(curX, y)) break;  // stop showing moves when reach first piece in the way
		SDL_SetRenderDrawColor(renderer, 79, 55, 158, 90);
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

		r.x = curX + 30;
		r.y = y + 30;
		SDL_RenderFillRect(renderer, &r);
		freeMoves.push_back({ curX, y });
	}
}

void ChessBoard::generateKnightMoves()
{
	SDL_Rect r;
	r.h = 60;
	r.w = 60;
	int newX, newY;
	int curX = curChessPiece->GetX();
	int curY = curChessPiece->GetY();
	freeMoves.clear();  // clear free moves because they might be for last chess piece
	
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
			if (checkIfSquareHasPiece(newX, newY))  // if square is taken by another piece then don't show free move there
				continue;
			SDL_SetRenderDrawColor(renderer, 79, 55, 158, 90);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

			// place offset so we draw move placeholder in middle of tile
			r.x = newX + 30;
			r.y = newY + 30;
			SDL_RenderFillRect(renderer, &r);
			freeMoves.push_back({ newX, newY });
		}
	}
}

void ChessBoard::generateBishopMoves()
{
	SDL_Rect r;
	r.h = 60;
	r.w = 60;
	int curX = curChessPiece->GetX();
	int curY = curChessPiece->GetY();
	if (curChessPiece->GetID() != QUEEN) freeMoves.clear();  // clear free moves because they might be for last chess piece

	// Draw moves in top-left direction
	for (int x = curX - 120, y = curY - 120; x >= 0 && y >= 0; x -= 120, y -= 120)
	{
		if (checkIfSquareHasPiece(x, y)) break;  // stop showing moves when reach first piece in the way
		SDL_SetRenderDrawColor(renderer, 79, 55, 158, 90);
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

		r.x = x + 30;
		r.y = y + 30;
		SDL_RenderFillRect(renderer, &r);
		freeMoves.push_back({ x, y });
	}

	// Draw moves in top-right direction
	for (int x = curX + 120, y = curY - 120; y >= 0 && x < 960; x += 120, y -= 120)
	{
		if (checkIfSquareHasPiece(x, y)) break;  // stop showing moves when reach first piece in the way
		SDL_SetRenderDrawColor(renderer, 79, 55, 158, 90);
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

		r.x = x + 30;
		r.y = y + 30;
		SDL_RenderFillRect(renderer, &r);
		freeMoves.push_back({ x, y });
	}

	// Draw moves in bottom-right direction
	for (int x = curX + 120, y = curY + 120; x < 960 && y < 960; x += 120, y += 120)
	{
		if (checkIfSquareHasPiece(x, y)) break;  // stop showing moves when reach first piece in the way
		SDL_SetRenderDrawColor(renderer, 79, 55, 158, 90);
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

		r.x = x + 30;
		r.y = y + 30;
		SDL_RenderFillRect(renderer, &r);
		freeMoves.push_back({ x, y });
	}

	// Draw moves in bottom-left direction
	for (int x = curX - 120, y = curY + 120; x >= 0 && y < 960; x -= 120, y += 120)
	{
		if (checkIfSquareHasPiece(x, y)) break;  // stop showing moves when reach first piece in the way
		SDL_SetRenderDrawColor(renderer, 79, 55, 158, 90);
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

		r.x = x + 30;
		r.y = y + 30;
		SDL_RenderFillRect(renderer, &r);
		freeMoves.push_back({ x, y });
	}
}

void ChessBoard::generateKingMoves()
{
	SDL_Rect r;
	r.h = 60;
	r.w = 60;
	int newX, newY;
	int curX = curChessPiece->GetX();
	int curY = curChessPiece->GetY();
	freeMoves.clear();  // clear free moves because they might be for last chess piece
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
			if (checkIfSquareHasPiece(newX, newY)) continue;
			SDL_SetRenderDrawColor(renderer, 79, 55, 158, 90);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

			// place offset so we draw move placeholder in middle of tile
			r.x = newX + 30;
			r.y = newY + 30;
			SDL_RenderFillRect(renderer, &r);
			freeMoves.push_back({ newX, newY });
		}
	}
}

void ChessBoard::generateBlackPawnMoves()
{
	// TODO check if its first pawn move of the game
	SDL_Rect r;
	r.h = 60;
	r.w = 60;
	SDL_SetRenderDrawColor(renderer, 79, 55, 158, 90);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	freeMoves.clear();  // clear free moves because they might be for last chess piece
	
	if (checkIfSquareHasPiece(curChessPiece->GetX(), curChessPiece->GetY() - 120)) return; // if there is piece on next square return without free moves
	
	r.x = curChessPiece->GetX() + 30;
	r.y = curChessPiece->GetY() - 90;
	SDL_RenderFillRect(renderer, &r);
	freeMoves.push_back({ curChessPiece->GetX(), curChessPiece->GetY() - 120 });
	
	if (checkIfSquareHasPiece(curChessPiece->GetX(), curChessPiece->GetY() - 240)) return; // if there is piece on next square return without free moves

	r.x = curChessPiece->GetX() + 30;
	r.y = curChessPiece->GetY() - 210;
	SDL_RenderFillRect(renderer, &r);
	freeMoves.push_back({ curChessPiece->GetX(), curChessPiece->GetY() - 240 });
}

void ChessBoard::generateWhitePawnMoves()
{
	// TODO check if its first pawn move of the game
	SDL_Rect r;
	r.h = 60;
	r.w = 60;
	SDL_SetRenderDrawColor(renderer, 79, 55, 158, 90);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	freeMoves.clear();  // clear free moves because they might be for last chess piece
	
	if (checkIfSquareHasPiece(curChessPiece->GetX(), curChessPiece->GetY() + 120)) return; // if there is piece on next square return without free moves

	r.x = curChessPiece->GetX() + 30;
	r.y = curChessPiece->GetY() + 150;
	SDL_RenderFillRect(renderer, &r);
	freeMoves.push_back({ curChessPiece->GetX(), curChessPiece->GetY() + 120 });

	if (checkIfSquareHasPiece(curChessPiece->GetX(), curChessPiece->GetY() + 240)) return; // if there is piece on next square return without free moves

	r.x = curChessPiece->GetX() + 30;
	r.y = curChessPiece->GetY() + 270;
	SDL_RenderFillRect(renderer, &r);
	freeMoves.push_back({ curChessPiece->GetX(), curChessPiece->GetY() + 240 });
}

void ChessBoard::MovePiece(int deltaX, int deltaY)
{
	if (curChessPiece != nullptr)
		curChessPiece->Move(deltaX, deltaY);
}

void ChessBoard::UpdateMovedPos(const int mouseX, const int mouseY)
{
	if (curChessPiece != nullptr)
	{
		for (auto& target : freeMoves)
		{
			if ((mouseX >= target.first && mouseX < (target.first + 120)) 
				&& (mouseY >= target.second && mouseY < (target.second + 120)))
			{
				curChessPiece->setPos(target.first, target.second);
				curChessPiece = nullptr;
				return;
			}
		}
		curChessPiece->ResetPos();
		curChessPiece = nullptr;
	}
}

void ChessBoard::Init() const
{
	Draw();
}

void ChessBoard::InitPieces()
{
	createPieces(chessPieces, 0, 0, "assets/w_");
	createPieces(chessPieces, 0, chessBoardH - 120, "assets/b_");
}

int ChessBoard::findPieceId(std::string_view& name)
{
	if (name == "rook") return ROOK;
	if (name == "knight") return KNIGHT;
	if (name == "bishop") return BISHOP;
	if (name == "king") return KING;
	if (name == "queen") return QUEEN;
}

void ChessBoard::createPieces(std::vector<ChessPiece>& pieces, int startX, int startY, std::string_view prefix)
{
	std::vector<std::string_view> basePieces = { "rook", "knight", "bishop", "king", "queen", "bishop", "knight", "rook" };
	std::vector<std::string_view> pawns = { "pawn", "pawn", "pawn", "pawn", "pawn", "pawn", "pawn", "pawn" };
	int x = startX, y = startY;
	std::string path;
	std::string_view imageType = ".png";
	
	for (auto& it : basePieces)
	{
		path.append(prefix).append(it).append(imageType);
		pieces.emplace_back(ChessPiece(path, x, y, renderer, findPieceId(it)));  // Use emplace_back to not create temporary copy of constructing object

		x += 120;  // move to next tile
		path.clear();  // clear the path for next iteration
	}

	x = 0;
	int pieceId;
	if (prefix.find("/w_") != std::string_view::npos) {
		y += 120;
		pieceId = W_PAWN;
	}  // check if drawing white pieces or black
	else {
		pieceId = B_PAWN;
		y -= 120;
	}
	
	for (auto& it : pawns)
	{
		path.append(prefix).append(it).append(imageType);
		pieces.emplace_back(ChessPiece(path, x, y, renderer, pieceId));

		x += 120;
		path.clear();
	}
}

ChessBoard::~ChessBoard()
{
}
