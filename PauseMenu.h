#pragma once
#include "Button.h"

class PauseMenu
{
private:

	sf::Font& font;
	sf::Text menuText;

	sf::RectangleShape background;
	sf::RectangleShape container;

	std::map<std::string, Button*> buttons;

public:
	PauseMenu(sf::VideoMode& vm, sf::Font& font);
	virtual ~PauseMenu();

	std::map<std::string, Button*>& getButtons();

	const bool isButtonPressed(const std::string key);
	void update(const sf::Vector2i& mousePosWindow);
	void render(sf::RenderTarget* target);
};

