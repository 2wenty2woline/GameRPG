#include "Game.h"

                                        // Initialize function
void Game::initVariables()
{
	window		= NULL;
	fullscreen	= false;
	dt			= 0.f;
}

void Game::initWindow()
{
	std::ifstream	ifs("Config/window.ini");
	videoModes = sf::VideoMode::getFullscreenModes();

	std::string		title = "None";
	sf::VideoMode	window_bounds = sf::VideoMode().getDesktopMode();
	unsigned		framerate_limit = 120;
	bool			vertical_sync_enable = false;
	bool			fullscreen = false;
	unsigned		antialiasing_level = 0;

	if (ifs.is_open())
	{
		std::getline(ifs, title);
		ifs >> window_bounds.width >> window_bounds.height;
		ifs >> fullscreen;
		ifs >> framerate_limit;
		ifs >> vertical_sync_enable;
		ifs >> antialiasing_level;
	}

	ifs.close();

	this->fullscreen = fullscreen;
	windowSettings.antialiasingLevel	= antialiasing_level;
	if (this->fullscreen)
	{
		window = new sf::RenderWindow(sf::VideoMode(window_bounds), title, sf::Style::Fullscreen, windowSettings);
	}
	else
	{
		window = new sf::RenderWindow(sf::VideoMode(window_bounds), title,
									  sf::Style::Titlebar | sf::Style::Close, windowSettings);
	}

	window->setFramerateLimit(framerate_limit);
	window->setVerticalSyncEnabled(vertical_sync_enable);
}

void Game::initKeys()
{
	std::ifstream ifs("Config/supported_keys.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		int key_value = 0;
		
		while (ifs >> key >> key_value)
		{
			supportedKeys[key] = key_value;
		}
	}

	ifs.close();

	for (auto i : supportedKeys)
	{
		std::cout << i.first << " " << i.second << std::endl;
	}
}

void Game::initStates()
{
	states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states));
}

										// Const-Dest
Game::Game()
{
	window = nullptr;

	initWindow();
	initKeys();
	initStates();
}

Game::~Game()
{
    delete window;

	while (!states.empty())
	{
		delete states.top();
		states.pop();
	}
}

										// Functions
void Game::endApplication()
{
	std::cout << "End Application!" << std::endl;
}

void Game::updateSFMLEvents()
{
	while (window->pollEvent(sfEvent))
	{
		if (sfEvent.type == sf::Event::Closed)
			window->close();
	}
}

void Game::updateDt()
{
										// Update the dt variable witht the time 

	dt = dtClock.restart().asSeconds();

}

void Game::update()
{
	updateSFMLEvents();

										// Update items
	if (!states.empty())
	{
		states.top()->update(this->dt);

		if (states.top()->getQuit())
		{
			states.top()->endState();
			delete this->states.top();
			states.pop();
		}
	}
										// Application End
	else
	{
		endApplication();
		window->close();
	}
}

void Game::render()
{
	window->clear();

										// Render items
	if (!states.empty())
		states.top()->render();

	window->display();
}

void Game::run()
{
	while (window->isOpen())
	{
		updateDt();
        update();
        render();
	}
}