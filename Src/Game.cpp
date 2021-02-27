#include "Game.h"
#include "ECS/Components.h"

using namespace rapidxml;
using namespace std;

Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

bool Game::isRunning = false;
bool Game::isPaused = false;
Vector2D Game::mouse;
xml_document<> doc;
xml_node<>* root_node = NULL;

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

		TTF_Init();

		isRunning = true;

		changeScene(2);

	}
}

auto& layer1(manager.getGroup(Game::Layer1));
auto& layer2(manager.getGroup(Game::Layer2));
auto& layer3(manager.getGroup(Game::Layer3));
auto& layer4(manager.getGroup(Game::Layer4));
auto& paused(manager.getGroup(Game::Paused));

void Game::handleEvents()
{
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_MOUSEMOTION:
		Game::mouse.x = event.motion.x;
		Game::mouse.y = event.motion.y;
		break;
	default:
		break;
	}
}

void Game::update()
{

	if (!isPaused) {
		for (auto& e : layer1)
		{
			e->update();
		}
		for (auto& e : layer2)
		{
			e->update();
		}
		for (auto& e : layer3)
		{
			e->update();
		}
		for (auto& e : layer4)
		{
			e->update();
		}
	}
	else {
		for (auto& e : paused)
		{
			e->update();
		}
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);

	for (auto& e : layer1)
	{
		e->draw();
	}
	for (auto& e : layer2)
	{
		e->draw();
	}
	for (auto& e : layer3)
	{
		e->draw();
	}
	for (auto& e : layer4)
	{
		e->draw();
	}

	if (isPaused)
	{
		for (auto& e : paused)
		{
			e->draw();
		}
	}

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Game::changeScene(int sceneNum)
{
	switch (sceneNum)
	{
	case 0:
	{
		isRunning = false;
		break;
	}
	case 1:
	{
		isPaused = false;
		break;
	}
	case 2:
	{
		removeEntities();
		isPaused = false;

		auto& menu(manager.addEntity());
		auto& gameStart(manager.addEntity());
		auto& quit(manager.addEntity());

		menu.addComponent<Position>(0.0, 0.0, 800, 640);
		menu.addComponent<Static>("assets/main_menu.png");
		menu.addGroup(Layer1);

		gameStart.addComponent<Position>(550.0, 300.0, 95, 112);
		gameStart.addComponent<Text>("Start", 72, 3);
		gameStart.addGroup(Layer2);

		quit.addComponent<Position>(550.0, 400.0, 76, 112);
		quit.addComponent<Text>("Quit", 72, 0);
		quit.addGroup(Layer2);

		break;
	}
	case 3:
	{
		removeEntities();

		auto& player(manager.addEntity());
		auto& frame(manager.addEntity());
		auto& level1(manager.addEntity());
		auto& level2(manager.addEntity());
		auto& resumeGame(manager.addEntity());
		auto& exitGame(manager.addEntity());

		player.addComponent<Position>(272.0, 448.0, 32, 64);
		player.addComponent<Velocity>(5);
		player.addComponent<Sprite>("assets/wizard_a.png", true);
		player.getComponent<Sprite>().addAnimation(0, 5, 100);
		player.addComponent<Player>();
		player.addGroup(Layer2);

		frame.addComponent<Position>(0.0, 0.0, 800, 640);
		frame.addComponent<Static>("assets/frame.png");
		frame.addGroup(Layer4);

		level1.addComponent<Position>(0.0, -640.0, 576, 1280);
		level1.addComponent<Velocity>(1, 0.0f, 1.0f);
		level1.addComponent<Level>("assets/map.png");
		level1.addGroup(Layer1);

		level2.addComponent<Position>(0.0, -1920.0, 576, 1280);
		level2.addComponent<Velocity>(1, 0.0f, 1.0f);
		level2.addComponent<Level>("assets/map.png");
		level2.addGroup(Layer1);

		resumeGame.addComponent<Position>(231.0, 96.0, 114, 112);
		resumeGame.addComponent<Text>("Resume", 72, 1);
		resumeGame.addGroup(Paused);

		resumeGame.addComponent<Position>(256.0, 196.0, 76, 112);
		resumeGame.addComponent<Text>("Exit", 72, 2);
		resumeGame.addGroup(Paused);

		std::cout << "Parsing script data" << std::endl;

		// Read the file
		std::ifstream file ("XML/sample.xml");
		std::vector<char> buffer((std::istreambuf_iterator<char>(file)),
			std::istreambuf_iterator<char>());
		buffer.push_back('\0');

		// Parse the buffer
		doc.parse<0>(&buffer[0]);

		// Find out the root node
		root_node = doc.first_node("Script");

		// Iterate over the Script nodes
		for (xml_node<>* minion_node = root_node->first_node(0);
			minion_node; minion_node = minion_node->next_sibling())
		{
			float xPos = std::atof(minion_node->first_node("xPos")->value());
			float yPos = std::atof(minion_node->first_node("yPos")->value());
			int width = std::atoi(minion_node->first_node("width")->value());
			int height = std::atoi(minion_node->first_node("height")->value());
			int speed = std::atoi(minion_node->first_node("speed")->value());
			const char* path = minion_node->first_node("sprite")->value();

			auto& minion(manager.addEntity());

			minion.addComponent<Position>(xPos, yPos, width, height);
			minion.addComponent<Velocity>(speed, 0.0, 1.0);
			minion.addComponent<Sprite>(path);

			minion.addGroup(Layer3);
		}

		break;
	}
	default:
		break;
	}
}

void Game::removeEntities()
{
	for (auto& e : layer1)
	{
		e->destroy();
	}
	for (auto& e : layer2)
	{
		e->destroy();
	}
	for (auto& e : layer3)
	{
		e->destroy();
	}
	for (auto& e : layer4)
	{
		e->destroy();
	}
	for (auto& e : paused)
	{
		e->destroy();
	}
	manager.refresh();
}