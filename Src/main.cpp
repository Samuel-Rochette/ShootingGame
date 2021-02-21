#include "Game.h"

Game *game = nullptr;

// Entry point of the application
int main(int argc, char *argv[])
{
	// Sets FPS parameters
	const int FPS = 60;
	const int FRAME_DELAY = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	// Instantiate and initialize Game object
	game = new Game();
	game->init("GameWindow", 800, 640, false);

	// Start of the game loop
	while (game->running())
	{
		// Get the amount of time since the application was started
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		// Get the amount of time it took to execute one instance of the game loop
		frameTime = SDL_GetTicks() - frameStart;

		// If the amount of time it took to execute an instance of the game loop is
		// less than the FRAME_DELAY -> delay the next iteration of the loop
		if (FRAME_DELAY > frameTime)
		{
			SDL_Delay(FRAME_DELAY - frameTime);
		}

	}

	// End of the loop
	// Destroy Window/Renderer and close the application
	game->clean();
	return 0;
}