#include "Asteroid.h"
#include "AssetManager.h"
#include "Physics.h"

Asteroid::Asteroid(sf::Vector2f newPosition)
	: Physics()
{
	m_sprite.setTexture(AssetManager::RequestTexture("Assets/Asteroids/Asteroid01.png"));

	m_CollisionOffset = sf::Vector2f(0, 0);
	m_CollisionScale = sf::Vector2f(1.0f, 1.0f);
}

