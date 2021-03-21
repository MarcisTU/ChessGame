#include "ChessBoard.h"

ChessBoard::ChessBoard(int winHeight, int winWidth, SDL_Renderer* ren)
	: renderer(ren)
{
	letters = { "a", "b", "c", "d", "e", "f", "g", "h" };
	chessBoardH = winHeight;
	chessBoardW = winWidth;
}

void ChessBoard::Draw()
{
	for (int row = 0; row < chessBoardH; row+=120)
	{
		for (int col = 0; col < chessBoardW; col+=120)
		{
			chessTile.x = col;
			chessTile.y = row;
			chessTile.w = 120;
			chessTile.h = 120;

			int curColNum = col / 120;
			int curRowNum = row / 120;
			
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


void ChessBoard::Init()
{
	Draw();
}

ChessBoard::~ChessBoard()
{
}
