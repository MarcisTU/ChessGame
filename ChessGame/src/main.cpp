#include <iostream>
#include "Game.h"

// MAJOR TODOS LATER ON
// 1. Instead of "for loops" use algorithms library if possible
// 2. Factor out generate moves logic to seperate class ?Moves?

int main(int argc, char* argv[])
{
	Game game("Chess Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 960);

	if (!game.running())
	{
		std::cout << "Game was not created successfully." << std::endl;
		return -1;
	}
	
	game.Init();
	
	while (game.running())
	{
		game.handleEvents();
		game.update();
		game.render();
	}
	
	return 0;
}