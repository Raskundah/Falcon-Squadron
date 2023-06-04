#pragma once
#include "Screen.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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

// scream

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
    void PickUps(sf::Time frameTime);

    int WhichPickup();
    void TextHud();

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
    int MaxPickups;

    float MaxTime, remainingTime;;

    bool isBroken;

    std::vector<EnemyShip*> enemies, cleanShips;

    std::vector<Asteroid*> asteroids, cleanAsteroids;

    std::vector<Collectible*> pickups, cleanPickups;

    std::vector<SpriteObject*> toBeDeleted;

    sf::Time levelTime, waveTimer, asteroidTime;

    sf::Clock waveClock, levelClock;

    sf::Music gameMusic;

    sf::Font gameFont;

    sf::Text healthText, shieldText, timeText, scoreText;

    std::string timerString, healthString, shieldString, scoreString;

};
