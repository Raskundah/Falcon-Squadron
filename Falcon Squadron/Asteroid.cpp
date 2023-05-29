#include "Asteroid.h"
#include "AssetManager.h"
#include "Physics.h"
#include <cstdlib>

Asteroid::Asteroid(sf::Vector2f newPosition)
	: Physics()
	, speed(750)
	, firstSpawn(true)
{
	m_sprite.setTexture(AssetManager::RequestTexture("Assets/Asteroids/Asteroid01.png"));

	srand(time(NULL));

	m_CollisionOffset = sf::Vector2f(0, 0);
	m_CollisionScale = sf::Vector2f(1.0f, 1.0f);
}

void Asteroid::Update(sf::Time frameTime, sf::Vector2u levelSize)
{
	SetPosition(frameTime, levelSize);


}

void Asteroid::Draw(sf::RenderTarget& target)
{
	SpriteObject::Draw(target);
}

void Asteroid::HandleCollision(Physics& other)
{
	Physics::HandleCollision(other);
}

void Asteroid::SetPosition(sf::Time frameTime, sf::Vector2u levelSize)
{

	if (firstSpawn)
	{
		sf::Vector2f position;

		position.x = rand() % levelSize.x;
		position.y = rand() % levelSize.y;

		m_position = position;

		firstSpawn = false;
	}

	m_position.x -= speed * frameTime.asSeconds();
}

