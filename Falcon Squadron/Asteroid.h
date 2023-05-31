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

    void HandleCollision(Physics& other);
    void SetPosition(sf::Time frameTime, sf::Vector2u levelSize);

private:
    int speed;
    bool firstSpawn;

};
