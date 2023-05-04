#include "Physics.h"

Physics::Physics()
{
}

void Physics::Update(sf::Time _frameTime)
{
}

void Physics::Draw(sf::RenderTarget _target)
{
}

sf::Vector2f Physics::GetPosition()
{
    return sf::Vector2f();
}

void Physics::SetPosition(sf::Vector2f _newPosition)
{
}

bool Physics::CheckCollision(Physics other)
{
    return false;
}

void Physics::SetColliding(bool newColliding)
{
}

sf::Vector2f Physics::GetCOllisionDepth(Physics other)
{
    return sf::Vector2f();
}

void Physics::SetAlive(bool _alive)
{
}
