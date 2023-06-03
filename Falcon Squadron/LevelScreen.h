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
class EnemyShip;
class SpriteObject;

class LevelScreen :
    public Screen
{

public:
    LevelScreen(Game* newGamePointer);

    void Update(sf::Time frameTime) override;
    void Draw(sf::RenderTarget& target) override;
    void MakeAsteroids(sf::Time frameTime);

    void TriggerEndState(bool _win);
    void WhichShips();
    void CleanUp();

 

private:

    Player player;
    EndPanel endPanel;
    bool gameRunning;
    sf::Sprite background;
    sf::Vector2u bounds;
    MediumShip* mediumShip;
    EasyShip* easyShip;
    ChallengingShip* challengingShip;

    int currentLevel, maxEasy, maxMedium, maxChallenging;
    int currentEasy, currentMedium, currentChallenging;
    int maxAsteroids;

    std::vector<EnemyShip*> enemies;
    std::vector<EnemyShip*> cleanShips;

    std::vector<Asteroid*> asteroids;
    std::vector<Asteroid*> cleanAsteroids;

    std::vector<SpriteObject*> toBeDeleted;

    sf::Time levelTime;
    sf::Time asteroidTime;
};