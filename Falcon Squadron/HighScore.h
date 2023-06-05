#pragma once
#include "Screen.h"
#include "SFML/Graphics.hpp"

class Game;

class HighScore :
    public Screen
{
public:
    HighScore(Game* newGamePointer);

    void Update(sf::Time frameTime);
    void Draw(sf::RenderTarget& target);

protected:

private:
};

