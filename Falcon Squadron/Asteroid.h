#pragma once
#include "SpriteObject.h"
#include "Physics.h"
class Asteroid :
    public Physics
{
public:
    Asteroid();

    void Update(sf::Time frameTime, sf::Vector2u levelSize);
    void Draw(sf::RenderTarget& target);
    bool IsMarkedForDeletion() const;
    void SetMarkedForDeletion(bool value);
    sf::Clock GetAsteroidAliveTime();

    void HandleCollision(Physics& other);
    void SetPosition(sf::Time frameTime, sf::Vector2u levelSize);
    int GetDamage();

private:
    int speed, damageToPlayer;
    bool firstSpawn;
    bool markedForDeletion;


    sf::Time lifeTime;
    sf::Clock deleteTimer;

};
