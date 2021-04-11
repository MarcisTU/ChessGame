#include "pch.h"
#include "Game.h"

// MAJOR TODOS & - must do  // ? - optional but would be good
//
// TODO & Implement opponent's king capture "check" and block any moves that would leave king vulnerable
// TODO & Check if player has possible free moves left for king or other pieces to block opponents attacker/ or capture that piece. If not then opponent player wins. GAME OVER state also show only those free moves for King which won't put him in captured state.!
// TODO & Implement clashing on queen side and also king side
// TODO & El pasan move for pawns and pawn's being able to transform once reached other side of board
// TODO ? Instead of "for loops" use algorithms library if possible (optimize)

int main(int argc, char* args[])
{
	Game game("Chess Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 1040);

	if (!game.running())
		return -1;
	
	game.Init();
	
	while (game.running())
	{
		game.handleEvents();
		game.update();
		game.render();
	}
	
	return 0;
}