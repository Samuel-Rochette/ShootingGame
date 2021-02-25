#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "Vector2D.h"
#include <iostream>

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean();

	static void removeEntities();
	static void changeScene(int sceneNum);

	static SDL_Renderer *renderer;
	static SDL_Event event;
	static bool isRunning;

	static Vector2D mouse;

	enum groupLabels : std::size_t
	{
		Layer1,
		Layer2,
		Layer3
	};


private:
	SDL_Window *window;
};