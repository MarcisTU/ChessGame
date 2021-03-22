#include "ChessBoard.h"

ChessBoard::ChessBoard(int winHeight, int winWidth, SDL_Renderer* ren)
	: renderer(ren)
{
	letters = { "a", "b", "c", "d", "e", "f", "g", "h" };
	basePieces = {"rook", "knight", "bishop", "king", "queen", "bishop", "knight", "rook"};
	pawns = {"pawn", "pawn", "pawn", "pawn", "pawn", "pawn", "pawn", "pawn"};

	chessBoardH = winHeight;
	chessBoardW = winWidth;
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
	for (auto& it : whitePieces)
	{
		it.Render();
	}
	for (auto& it : blackPieces)
	{
		it.Render();
	}
}

void ChessBoard::Init() const
{
	Draw();
}

void ChessBoard::createPieces(std::vector<ChessPiece>& pieces, int startX, int startY, std::string prefix)
{
	int x = startX, y = startY;
	std::string path, imageType = ".png";

	for (auto& it : basePieces)
	{
		path.append(prefix).append(it).append(imageType);
		pieces.emplace_back(ChessPiece(path, x, y, renderer));  // Use emplace_back to not create temporary copy of constructing object

		x += 120;  // move to next tile
		path.clear();  // clear the path for next iteration
	}

	x = 0;
	if (prefix.find("/w_") != std::string::npos) y += 120;  // check if drawing white pieces or black
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
	createPieces(whitePieces, 0, 0, "assets/w_");
	createPieces(blackPieces, 0, chessBoardH - 120, "assets/b_");
}

ChessBoard::~ChessBoard()
{
}
