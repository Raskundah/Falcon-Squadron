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
#include "Collectible.h"
#include "HealthPickup.h"
#include "ShieldPickup.h"

class Game;
class Platform;
class EnemyShip;
class SpriteObject;

class LevelScreen :
    public Screen
{

public:
    LevelScreen(Game* newGamePointer); // constructor for the level screen which needs to point to the active game process. 

    void Update(sf::Time frameTime) override; // the override of draw.
    void Draw(sf::RenderTarget& target) override; //override of update. 
    void MakeAsteroids(sf::Time frameTime); // makes asteroids in level. It would be possible to do this in asteroid, but an asteroid doesn't need to know about all asteroids.

    void TriggerEndState(bool _win); //this is remnants from an old project, may use this to initiate high score transition. 
    void WhichShips(); // determines which ship vector generator to use, dependant on level.
    void CleanUp(); // cleans up unused ships and asteroids. 
    void NewCleanUp(); // does the same if the previous causes issues, thanks sarah!

    void Collision(); // keeps the collision code to keep the update function neat and tidy. If there's time I will refactor the collision into more OOp friendly design.

 

private:

    Player player;
    EndPanel endPanel;
    MediumShip* mediumShip;
    EasyShip* easyShip;
    ChallengingShip* challengingShip;
    HealthPickup* healthPickup;
    ShieldPickup* shieldPickup;
    

    sf::Sprite background;
    sf::Vector2u bounds;

    bool gameRunning;
    bool firstWave;
    int currentLevel, maxEasy, maxMedium, maxChallenging;
    int currentEasy, currentMedium, currentChallenging;
    int maxAsteroids;

    std::vector<EnemyShip*> enemies;
    std::vector<EnemyShip*> cleanShips;

    std::vector<Asteroid*> asteroids;
    std::vector<Asteroid*> cleanAsteroids; 

    std::vector<Collectible*> pickups;
    std::vector<Collectible*> cleanPickups;

    std::vector<SpriteObject*> toBeDeleted;

    sf::Time levelTime;
    sf::Time waveTimer;
    sf::Time asteroidTime;

    sf::Clock waveClock;
    sf::Clock levelClock;
};
