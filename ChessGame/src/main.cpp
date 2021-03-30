#include "SDL2/SDL.h"
#include <iostream>

#include "Game.h"

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