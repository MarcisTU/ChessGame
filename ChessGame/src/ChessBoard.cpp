#include "pch.h"
#include "ChessBoard.h"

ChessBoard::ChessBoard(int winHeight, int winWidth, SDL_Renderer* ren)
	: chessBoardH(winHeight), chessBoardW(winWidth), renderer(ren), curChessPiece(nullptr), engine(ren)
{}

void ChessBoard::Draw() const
{
	// TODO draw square names on board or on sides. ex. A1, A2, A3...
	int curRowNum = 0, curColNum = 0;
	SDL_Rect boardSquare;
	boardSquare.w = 120;
	boardSquare.h = 120;
	
	for (int row = 40; row < chessBoardH - 40; row+=120, curRowNum++) {
		for (int col = 0; col < chessBoardW; col+=120, curColNum++) {
			boardSquare.x = col;
			boardSquare.y = row;
			
			if ((curRowNum + curColNum) % 2 == 0) {
				// Set render color to White
				SDL_SetRenderDrawColor(renderer, 230, 230, 230, 255);
				SDL_RenderFillRect(renderer, &boardSquare);
			} else {
				// Set render color to Dark
				SDL_SetRenderDrawColor(renderer, 31, 48, 74, 255);
				SDL_RenderFillRect(renderer, &boardSquare);
			}
		}
		curColNum = 0;
	}

	// Draw top and bottom area for each player's captured pieces
	SDL_Rect playerArea;
	playerArea.w = chessBoardW;
	playerArea.h = 40;

	// Draw top player's area
	playerArea.x = 0;
	playerArea.y = 0;
	SDL_SetRenderDrawColor(renderer, 230, 230, 230, 255);
	SDL_RenderFillRect(renderer, &playerArea);

	// Draw bottom player's area
	playerArea.x = 0;
	playerArea.y = chessBoardH - 40;
	SDL_SetRenderDrawColor(renderer, 31, 48, 74, 255);
	SDL_RenderFillRect(renderer, &playerArea);
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

	// Render each player's captured pieces above or below the board
	if (!capturedPieces.empty()) {
		int whiteX = 0, blackX = 0;
		for (auto& it : capturedPieces)
		{
			// check for piece color
			if (it.GetColor() == WHITE)
			{
				it.setPos(whiteX, chessBoardH, 3, -37);
				it.setDimensions(24, 34);
				it.Render();
				whiteX += 40;
			} else
			{
				it.setPos(blackX, 0, 3, 3);
				it.setDimensions(24, 34);
				it.Render();
				blackX += 40;
			}
		}
	}
}

void ChessBoard::getClicked(int mouseX, int mouseY, int &curPieceColor)  // gets current clicked piece if any was selected
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
			curPieceColor = curChessPiece->GetColor();
		}
	}
}

void ChessBoard::showCurPieceMoves()
{
	if (curChessPiece != nullptr) {
		const int selectedPieceColor = curChessPiece->GetColor();
		switch (curChessPiece->GetID()) {
		case PAWN:
			selectedPieceColor == WHITE
				?
				engine.generateWhitePawnMoves(curChessPiece->GetX(), curChessPiece->GetY(), freeMoves, captureMoves, chessPieces, curChessPiece->firstMove(), selectedPieceColor)
				:
				engine.generateBlackPawnMoves(curChessPiece->GetX(), curChessPiece->GetY(), freeMoves, captureMoves, chessPieces, curChessPiece->firstMove(), selectedPieceColor);
			break;
		case ROOK:
			engine.generateRookMoves(curChessPiece->GetX(), curChessPiece->GetY(), freeMoves, captureMoves, chessPieces, selectedPieceColor);
			break;
		case KNIGHT:
			engine.generateKnightMoves(curChessPiece->GetX(), curChessPiece->GetY(), freeMoves, captureMoves, chessPieces, selectedPieceColor);
			break;
		case BISHOP:
			engine.generateBishopMoves(curChessPiece->GetX(), curChessPiece->GetY(), freeMoves, captureMoves, chessPieces, selectedPieceColor);
			break;
		case KING:
			engine.generateKingMoves(curChessPiece->GetX(), curChessPiece->GetY(), freeMoves, captureMoves, chessPieces, selectedPieceColor);
			break;
		case QUEEN:
			engine.generateRookMoves(curChessPiece->GetX(), curChessPiece->GetY(), freeMoves, captureMoves, chessPieces, selectedPieceColor);
			engine.generateBishopMoves(curChessPiece->GetX(), curChessPiece->GetY(), freeMoves, captureMoves, chessPieces, selectedPieceColor, true);
			break;
		default:
			break;
		}
	}
}

void ChessBoard::MovePiece(int deltaX, int deltaY) const
{
	if (curChessPiece != nullptr) curChessPiece->Move(deltaX, deltaY);
}

void ChessBoard::UpdateMovedPos(const int mouseX, const int mouseY, bool& isWhiteMove)
{
	if (curChessPiece != nullptr)
	{
		// *** Handle mouse button up on free move *** //
		for (auto& target : freeMoves)
		{
			if ((mouseX >= target.first && mouseX < (target.first + 120)) 
				&& (mouseY >= target.second && mouseY < (target.second + 120)))
			{
				curChessPiece->setPos(target.first, target.second);
				isWhiteMove = !isWhiteMove;
				std::cout << "Changing player: free move" << std::endl;
				// Mark chess piece as moved
				if (curChessPiece->firstMove()) curChessPiece->setFirstMove(false);
				curChessPiece = nullptr;
				return;
			}
		}
		// *** Handle mouse button up on capture move *** //
		for (auto& target : captureMoves)
		{
			if ((mouseX >= target.first && mouseX < (target.first + 120))
				&& (mouseY >= target.second && mouseY < (target.second + 120)))
			{
				int temp;
				int curX = curChessPiece->GetX();
				int curY = curChessPiece->GetY();
				
				// Remove to be captured chess piece
				removeCaptured(target.first, target.second);  // TODO draw captured piece for score

				getClicked(curX, curY, temp); //Removing element from vector have shifted it and our pointer is not pointing to right element, so we get curChessPiece again
				
				// Then move capturing chess piece to new position
				curChessPiece->setPos(target.first, target.second);
				// Switch player
				isWhiteMove = !isWhiteMove;
				std::cout << "Changing player: capture move" << std::endl;
				// Mark chess piece as moved
				if (curChessPiece->firstMove()) curChessPiece->setFirstMove(false);

				// Set current piece as nullptr to not point to the same piece next time
				curChessPiece = nullptr;
				return;
			}
		}
		curChessPiece->ResetPos();
		curChessPiece = nullptr;
	}
}

void ChessBoard::removeCaptured(int x, int y)
{
	for (auto it = chessPieces.begin(); it != chessPieces.end(); ++it) {
		if (it->GetX() == x && it->GetY() == y)
		{
			capturedPieces.emplace_back((*it));
			chessPieces.erase(it);
			break;  // piece is deleted so no need to iterate further
		}
	}
}

void ChessBoard::InitPieces()
{
	createPieces(chessPieces, 0, 40, "assets/w_");
	createPieces(chessPieces, 0, chessBoardH - 160, "assets/b_");
}

int ChessBoard::findPieceId(std::string_view& name)
{
	if (name == "rook") return ROOK;
	if (name == "knight") return KNIGHT;
	if (name == "bishop") return BISHOP;
	if (name == "king") return KING;
	if (name == "queen") return QUEEN;
	return PAWN;
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