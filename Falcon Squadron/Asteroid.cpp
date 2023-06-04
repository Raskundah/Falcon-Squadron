#include "Asteroid.h"
#include "AssetManager.h"
#include "Physics.h"
#include <cstdlib>

Asteroid::Asteroid()
	: Physics()
	, speed(250)
	, firstSpawn(true)
	, lifeTime(sf::seconds(10.f))
	, markedForDeletion(false)
	, damageToPlayer(25)
	, damageCounter()
{
	m_sprite.setTexture(AssetManager::RequestTexture("Assets/Asteroids/Asteroid 01.png"));

	m_CollisionOffset = sf::Vector2f(0, 0);
	m_CollisionScale = sf::Vector2f(1.0f, 1.0f);
	collisionType = CollisionType::CIRCLE;
}

void Asteroid::Update(sf::Time frameTime, sf::Vector2u levelSize)
{
	if (!Physics::GetAlive())
		return;

	m_position.x -= speed * frameTime.asSeconds();
	m_sprite.setPosition(GetPosition());

}

void Asteroid::Draw(sf::RenderTarget& target)
{
	if (!Physics::GetAlive())
		return;
	
	Physics::Draw(target);

	//target.draw(m_sprite);
}

bool Asteroid::IsMarkedForDeletion() const
{
	return markedForDeletion;
}

void Asteroid::SetMarkedForDeletion(bool value)
{
	markedForDeletion = value;
}

sf::Clock Asteroid::GetAsteroidAliveTime()
{
	return deleteTimer;
}

void Asteroid::HandleCollision(Physics& other)
{
	Physics::HandleCollision(other);
}

void Asteroid::SetPosition(sf::Time frameTime, sf::Vector2u levelSize)
{
	int minY = 0 + m_sprite.getGlobalBounds().height;
	int maxY = levelSize.y - m_sprite.getGlobalBounds().height;

	int minX = (levelSize.x / 6.0f) + m_sprite.getGlobalBounds().width;
	int maxX = levelSize.x - m_sprite.getGlobalBounds().width;

	int rangeY = maxY - minY;
	int rangeX = maxX - minX;

	if (firstSpawn)
	{
		sf::Vector2f position;

		position.x = rand() % rangeX + minX;
		position.y = rand() % rangeY;

		m_position = position;

		firstSpawn = false;

		m_sprite.setPosition(GetPosition());

	}

}

int Asteroid::GetDamage()
{
	return damageToPlayer;
}

void Asteroid::TakeDamage()
{
	damageCounter -= 1;
	if (damageCounter <= 0);
	{
		this->SetMarkedForDeletion(true);
	}
}


