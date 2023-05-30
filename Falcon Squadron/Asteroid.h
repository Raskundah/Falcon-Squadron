#pragma once
#include "SpriteObject.h"
#include "Physics.h"
class Asteroid :
    public Physics
{
public:
    Asteroid(sf::Vector2f newPosition);
    
};
