#include "ChessBoard.h"

ChessBoard::ChessBoard(int winHeight, int winWidth, SDL_Renderer* ren)
	: chessBoardH(winHeight), chessBoardW(winWidth), renderer(ren)
{
	letters = { "a", "b", "c", "d", "e", "f", "g", "h" };
	basePieces = {"rook", "knight", "bishop", "king", "queen", "bishop", "knight", "rook"};
	pawns = {"pawn", "pawn", "pawn", "pawn", "pawn", "pawn", "pawn", "pawn"};
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

void ChessBoard::MovePiece(int deltaX, int deltaY)
{
	if (curChessPiece != nullptr)
		curChessPiece->Move(deltaX, deltaY);
}

void ChessBoard::UpdateMovedPos()
{
	if (curChessPiece != nullptr)
	{
		curChessPiece->ResetPos();
		curChessPiece = nullptr;
	}
}

void ChessBoard::Init() const
{
	Draw();
}

void ChessBoard::createPieces(std::vector<ChessPiece>& pieces, int startX, int startY, std::string_view prefix)
{
	int x = startX, y = startY;
	std::string path;
	std::string_view imageType = ".png";
	
	for (auto& it : basePieces)
	{
		path.append(prefix).append(it).append(imageType);
		pieces.emplace_back(ChessPiece(path, x, y, renderer));  // Use emplace_back to not create temporary copy of constructing object

		x += 120;  // move to next tile
		path.clear();  // clear the path for next iteration
	}

	x = 0;
	if (prefix.find("/w_") != std::string_view::npos) y += 120;  // check if drawing white pieces or black
	else y -= 120;
	
	for (auto& it : pawns)
	{
		path.append(prefix).append(it).append(imageType);
		pieces.emplace_back(ChessPiece(path, x, y, renderer));

		x += 120;
		path.clear();
	}
}

void ChessBoard::InitPieces()
{
	createPieces(chessPieces, 0, 0, "assets/w_");
	createPieces(chessPieces, 0, chessBoardH - 120, "assets/b_");
}

ChessBoard::~ChessBoard()
{
}
