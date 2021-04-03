#include "ChessBoard.h"

ChessBoard::ChessBoard(int winHeight, int winWidth, SDL_Renderer* ren)
	: chessBoardH(winHeight), chessBoardW(winWidth), renderer(ren), curChessPiece(nullptr)
{
	engine = GameLogic(renderer);
}

void ChessBoard::Draw() const
{
	SDL_Rect chessTile;
	chessTile.w = 120;
	chessTile.h = 120;
	
	for (int row = 0; row < chessBoardH; row+=120)
	{
		for (int col = 0; col < chessBoardW; col+=120)
		{
			chessTile.x = col;
			chessTile.y = row;

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
	const int curColor = curChessPiece->GetColor();
	if (curChessPiece != nullptr)
		switch(curChessPiece->GetID())
		{
		case PAWN:
			curColor == WHITE
			? 
			engine.generateWhitePawnMoves(curChessPiece->GetX(), curChessPiece->GetY(), freeMoves, captureMoves, chessPieces, curChessPiece->firstmove(), curColor)
			: 
			engine.generateBlackPawnMoves(curChessPiece->GetX(), curChessPiece->GetY(), freeMoves, captureMoves, chessPieces, curChessPiece->firstmove(), curColor);
			break;
		case ROOK:
			engine.generateRookMoves(curChessPiece->GetX(), curChessPiece->GetY(), freeMoves, chessPieces);
			break;
		case KNIGHT:
			engine.generateKnightMoves(curChessPiece->GetX(), curChessPiece->GetY(), freeMoves, chessPieces);
			break;
		case BISHOP:
			engine.generateBishopMoves(curChessPiece->GetX(), curChessPiece->GetY(), freeMoves, chessPieces);
			break;
		case KING:
			engine.generateKingMoves(curChessPiece->GetX(), curChessPiece->GetY(), freeMoves, chessPieces);
			break;
		case QUEEN:
			engine.generateRookMoves(curChessPiece->GetX(), curChessPiece->GetY(), freeMoves, chessPieces);
			engine.generateBishopMoves(curChessPiece->GetX(), curChessPiece->GetY(), freeMoves, chessPieces, true);
			break;
		default:
			break;
		}
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
				// Mark chess piece as moved
				curChessPiece->setFirstMove(false);
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
	std::string_view basePieces[8] = { "rook", "knight", "bishop", "king", "queen", "bishop", "knight", "rook" };
	std::string_view pawns[8] = { "pawn", "pawn", "pawn", "pawn", "pawn", "pawn", "pawn", "pawn" };
	std::string path;
	std::string_view imageType = ".png";
	int pieceColor = prefix.find("/w") != std::string::npos ? WHITE : BLACK;
	
	for (auto& it : basePieces)
	{
		path.append(prefix).append(it).append(imageType);
		pieces.emplace_back(ChessPiece(path, startX, startY, renderer, findPieceId(it), pieceColor));  // Use emplace_back to not create temporary copy of constructing object
		startX += 120;  // move to next tile
		path.clear();  // clear the path for next iteration
	}

	startX = 0;
	pieceColor == WHITE ? startY += 120 : startY -= 120;
	
	for (auto& it : pawns)
	{
		path.append(prefix).append(it).append(imageType);
		pieces.emplace_back(ChessPiece(path, startX, startY, renderer, PAWN, pieceColor));
		startX += 120;
		path.clear();
	}
}