#include "Game.h"
#include "ECS/Components.h"

Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

bool Game::isRunning = false;

auto& player(manager.addEntity());
auto& frame(manager.addEntity());
auto& level1(manager.addEntity());
auto& level2(manager.addEntity());

Game::Game()
{}

Game::~Game()
{}

// Initialize function invoked before the start of the game loop
void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;
	
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		// Create SDL Window and Renderer
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isRunning = true;

		player.addComponent<Position>(224.0, 448.0, 32, 64);
		player.addComponent<Velocity>(5);
		player.addComponent<Sprite>("assets/wizard_a.png", true);
		player.getComponent<Sprite>().addAnimation(0, 5, 50);
		player.addComponent<Player>();
		player.addGroup(Layer2);

		frame.addComponent<Position>(0.0, 0.0, 800, 640);
		frame.addComponent<Frame>("assets/frame.png");
		frame.addGroup(Layer2);

		level1.addComponent<Position>(0.0, -640.0, 576, 1280);
		level1.addComponent<Velocity>(1, 0.0f, 1.0f);
		level1.addComponent<Level>("assets/map.png");
		level1.addGroup(Layer1);

		level2.addComponent<Position>(0.0, -1920.0, 576, 1280);
		level2.addComponent<Velocity>(1, 0.0f, 1.0f);
		level2.addComponent<Level>("assets/map.png");
		level2.addGroup(Layer1);
	}
}

auto& layer1(manager.getGroup(Game::Layer1));

void Game::handleEvents()
{
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT :
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update()
{

	for (auto& e : layer1)
	{
		e->update();
	}

	player.update();

}

void Game::render()
{
	SDL_RenderClear(renderer);

	for (auto& e : layer1)
	{
		e->draw();
	}

	frame.draw();
	player.draw();

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}