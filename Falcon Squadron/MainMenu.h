#pragma once
#include "Screen.h"
#include "SFML/Graphics.hpp"

class Game;

class MainMenu :
    public Screen
{
public:
    MainMenu(Game* newGamePointer);

    void Update(sf::Time frameTime);
    void Draw(sf::RenderTarget& target);

protected:

private:
    sf::Text mainMenuText;
    sf::Font menuFont;
};

