#pragma once
#include "Screen.h"
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "EndPanel.h"

class Game;
class Platform;

class LevelScreen :
    public Screen
{

public:
    LevelScreen(Game* newGamePointer);

    void Update(sf::Time frameTime) override;
    void Draw(sf::RenderTarget& target) override;

    void TriggerEndState(bool _win);

private:

    Player player;
    EndPanel endPanel;
    bool gameRunning;
    sf::Sprite background;
    sf::Vector2u bounds;

    std::vector<Platform*> platforms;
    
};