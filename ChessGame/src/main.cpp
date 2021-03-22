#include "SDL2/SDL.h"
#include <iostream>

#include "Game.h"

int main(int argc, char* argv[])
{
	Game game("Chess Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 960);

	// Check if game object has been created successfully
	if (!game.running())
	{
		std::cout << "Game was not created successfully." << std::endl;
		return -1;
	}
	
	// Init game state
	game.Init();
	
	while (game.running())
	{
		// Handle Mouse/Keyboard events from player
		game.handleEvents();
		// Update ChessBoard with new data
		game.update();
		// Draw the new changes
		game.render();
	}
	
	return 0;
}