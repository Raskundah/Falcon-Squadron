#pragma once
#include "Screen.h"
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "EndPanel.h"
#include "Asteroid.h"
#include "MediumShip.h"
#include "EasyShip.h"
#include "ChallengingShip.h"
#include "EnemyShip.h"

class Game;
class Platform;

class LevelScreen :
    public Screen
{

public:
    LevelScreen(Game* newGamePointer);

    void Update(sf::Time frameTime) override;
    void Draw(sf::RenderTarget& target) override;
    void MakeAsteroids(sf::Time frameTime);

    void TriggerEndState(bool _win);

private:

    Player player;
    EndPanel endPanel;
    bool gameRunning;
    sf::Sprite background;
    sf::Vector2u bounds;
    MediumShip mediumShip;
    EasyShip easyShip;
    ChallengingShip challengingShip;

    int currentLevel;
    int maxAsteroids;

    std::vector<Asteroid> asteroids;
    std::vector<EnemyShip*> enemies;
};