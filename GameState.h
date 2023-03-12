#pragma once
#include "State.h"
#include "PauseMenu.h"

class GameState :
    public State
{
private:
    sf::VideoMode resolution;
    sf::Font font;
    PauseMenu* pmenu;

    sf::Clock keyTimer;
    float keyTimeMax;

    Player* player;

    void initKeybinds();
    void initFonts();
    void initTexture();
    void initPauseMenu();
    void initKeyTime();
    void initPlayers();

public:
    GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~GameState();

    const bool getKeyTime();

    void updateInput(const float& dt);
    void updatePlayerInput(const float& dt);
    void updatePauseMenuButtons();
    void update(const float& dt);
    void render(sf::RenderTarget* target = NULL);
};
