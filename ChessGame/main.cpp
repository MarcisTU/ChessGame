#include <SDL2/SDL.h>
#include <iostream>
#include <memory>

#include "Game.h"

int main(int argc, char* argv[])
{
	// Set fps of game (usually 60Hz monitors)
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	// Use smart-pointer to take care of calling delete automatically!
	std::unique_ptr<Game> game(new Game("Chess Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, false));

	while (game->running())
	{
		frameStart = SDL_GetTicks();

		// Handle Mouse/Keyboard events from player
		game->handleEvents();
		// Update ChessBoard with new data
		game->update();
		// Draw the new changes
		game->render();

		// Delay time in case for different computers that run this program
		// Without Limiting frame rate some computers will have different experience
		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}
	
	return 0;
}