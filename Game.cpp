#include "stdafx.h"
#include "Game.h"

void Game::initVariables()
{
	this->window = NULL;
	this->fullscreen = false;

	this->dt = 0.f;
}

void Game::initWindow()
{
	this->resolution = sf::VideoMode::getDesktopMode();
	this->videomodes = sf::VideoMode::getFullscreenModes();
	this->resolution.width = 1920;
	this->resolution.height = 1080;
	bool fullscreen = false;
	unsigned antialiasing_level = 0;

	this->fullscreen = fullscreen;
	windowSettings.antialiasingLevel = antialiasing_level;
	if (this->fullscreen)
		this->window = new sf::RenderWindow(this->resolution, "title", sf::Style::Fullscreen, windowSettings);
	else
		this->window = new sf::RenderWindow(this->resolution, "title", sf::Style::Titlebar | sf::Style::Close, windowSettings);

	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initKeys()
{
	this->supportedKeys["Escape"] = sf::Keyboard::Key::Escape;
	this->supportedKeys["A"] = sf::Keyboard::Key::A;
	this->supportedKeys["D"] = sf::Keyboard::Key::D;
	this->supportedKeys["W"] = sf::Keyboard::Key::W;
	this->supportedKeys["S"] = sf::Keyboard::Key::S;

}

void Game::initStates()
{
	this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states));
}


Game::Game()
{
	this->initWindow();
	this->initKeys();
	this->initStates();
}

Game::~Game()
{
	delete this->window;

	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}

void Game::endApplication()
{
	std::cout << "Game closed\n";
}

void Game::updateDt()
{
	this->dt = this->dtClock.restart().asSeconds();


}

void Game::updateSFMLEvents()
{
	while (this->window->pollEvent(this->e))
	{
		if (this->e.type == sf::Event::Closed)
			this->window->close();
	}
}

void Game::update()
{
	this->updateSFMLEvents();

	if (!this->states.empty())
	{
		this->states.top()->update(this->dt);

		if (this->states.top()->getQuit())
		{
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
		}
	}
	else
	{
		this->endApplication();
		this->window->close();
	}
}

void Game::render()
{
	this->window->clear();

	if (!this->states.empty())
		this->states.top()->render();

	this->window->display();
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->updateDt();
		this->update();
		this->render();
	}
}
