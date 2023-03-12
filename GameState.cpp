#include "stdafx.h"
#include "GameState.h"

void GameState::initKeybinds()
{
	this->keybinds["CLOSE"] = this->supportedKeys->at("Escape");
	this->keybinds["MOVE_LEFT"] = this->supportedKeys->at("A");
	this->keybinds["MOVE_RIGHT"] = this->supportedKeys->at("D");
	this->keybinds["MOVE_UP"] = this->supportedKeys->at("W");
	this->keybinds["MOVE_DOWN"] = this->supportedKeys->at("S");
}

void GameState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/PixellettersFull.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void GameState::initTexture()
{
	if (!this->textures["PLAYER_IDLE"].loadFromFile("Textures/player.png"))
	{
		throw "ERROR::GAMESTATE::COULD NOT LOAD PLAYER IDLE TEXTURE";
	}
}

void GameState::initPauseMenu()
{
	this->resolution = sf::VideoMode::getDesktopMode();
	this->resolution.width = 1920;
	this->resolution.height = 1080;
	this->pmenu = new PauseMenu(this->resolution, this->font);
}

void GameState::initKeyTime()
{
	this->keyTimeMax = 0.3f;
	this->keyTimer.restart();
}

void GameState::initPlayers()
{
	this->player = new Player(0, 0, &this->textures["PLAYER_IDLE"]);
}

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initKeybinds();
	this->initFonts();
	this->initTexture();
	this->initPauseMenu();
	this->initKeyTime();
	this->initPlayers();
}

GameState::~GameState()
{
	delete this->pmenu;
	delete this->player;
}

const bool GameState::getKeyTime()
{
	if (this->keyTimer.getElapsedTime().asSeconds() >= this->keyTimeMax)
	{
		this->keyTimer.restart();
		return true;
	}

	return false;
}


void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime())
	{
		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
	}

}

void GameState::updatePlayerInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
		this->player->move(dt, -1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
		this->player->move(dt, 1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
		this->player->move(dt, 0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
		this->player->move(dt, 0.f, 1.f);
}

void GameState::updatePauseMenuButtons()
{
	if(this->pmenu->isButtonPressed("RESUME"))
		this->unpauseState();
	if (this->pmenu->isButtonPressed("EXIT_GAME_STATE"))
		this->endState();
}

void GameState::update(const float& dt)
{
	this->updateMousePosition();
	this->updateKeytime(dt);
	this->updateInput(dt);
	
	if (!this->paused) //Unpaused update
	{

		this->updatePlayerInput(dt);

		this->player->update(dt);
	}
	else //Paused update
	{
		this->pmenu->update(this->mousePosWindow);
		this->updatePauseMenuButtons();
	}
	

}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	if (this->paused) //Pause menu render
	{
		this->pmenu->render(target);
	}

	this->player->render(target);
}
