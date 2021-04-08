#pragma once
#include "pch.h"

#include "ChessBoard.h"

class Game
{
public:
	Game(std::string title, int xpos, int ypos, int width, int height);
	// Delete default generated copy constructor and assignment operator because we don't want to copy Game object (Rule of Five). If we delete one default then we got to delete all of them
	Game(const Game&) = delete;				 // Copy constructor
	Game& operator=(Game&) = delete;		 // Copy assignment operator
	Game(Game&& other) = delete;			 // Move constructor
	Game& operator=(Game&& other) = delete;  // Move assignment operator
	~Game();

	void Init();
	
	void handleEvents();
	void update();
	void render();

	bool running() { return isRunning; }
private:
	int winHeight, winWidth, curPieceColor;
	bool isRunning, leftMouseBtnDown, isWhiteMove = true;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Point mousePos, lastMousePos;
	ChessBoard chessBoard;
};