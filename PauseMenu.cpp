#include "stdafx.h"
#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::VideoMode& vm, sf::Font& font)
	: font(font)
{
	//Init background
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(vm.width),
			static_cast<float>(vm.height)
		)
	);
	this->background.setFillColor(sf::Color(20, 20, 20, 100));

	this->container.setSize(
		sf::Vector2f(
			static_cast<float>(vm.width) / 4.f,
			static_cast<float>(vm.height)
		)
	);
	this->container.setFillColor(sf::Color(20, 20, 20, 200));
	this->container.setPosition(
		static_cast<float>(vm.width) / 2.f - this->container.getSize().x / 2.f,
		30.f
	);

	this->menuText.setFont(font);
	this->menuText.setFillColor(sf::Color(255, 255, 255, 200));
	this->menuText.setCharacterSize(static_cast<unsigned>((vm.width + vm.height) / 60));
	this->menuText.setString("PAUSED");
	this->menuText.setPosition(
		this->container.getPosition().x + this->container.getSize().x / 2.f - this->menuText.getGlobalBounds().width / 2.f,
		this->container.getPosition().y + std::floor(static_cast<float>(vm.height) * (4.f / 100.f))
	);

	this->buttons["RESUME"] = new Button(this->container.getPosition().x + this->container.getSize().x / 2.f - (std::floor(static_cast<float>(vm.width) * (13.f / 100.f))) / 2.f,
		std::floor(static_cast<float>(vm.height) * (44.f/ 100.f)), std::floor(static_cast<float>(vm.width) * (13.f / 100.f)), 
		std::floor(static_cast<float>(vm.height) * (6.f / 100.f)), &this->font, "Continue",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	this->buttons["EXIT_GAME_STATE"] = new Button(this->container.getPosition().x + this->container.getSize().x / 2.f - (std::floor(static_cast<float>(vm.width) * (13.f / 100.f))) / 2.f,
		std::floor(static_cast<float>(vm.height) * (74.f / 100.f)), std::floor(static_cast<float>(vm.width) * (13.f / 100.f)),
		std::floor(static_cast<float>(vm.height) * (6.f / 100.f)), &this->font, "Abandon Challenge",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}

PauseMenu::~PauseMenu()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

std::map<std::string, Button*>& PauseMenu::getButtons()
{
	return this->buttons;
}

const bool PauseMenu::isButtonPressed(const std::string key)
{
	return this->buttons[key]->isPressed();
}

void PauseMenu::update(const sf::Vector2i& mousePosWindow)
{
	for (auto& i : this->buttons)
	{
		i.second->update(mousePosWindow);
	}
}

void PauseMenu::render(sf::RenderTarget* target)
{

	target->draw(this->background);
	target->draw(this->container);

	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}

	target->draw(this->menuText);
}
