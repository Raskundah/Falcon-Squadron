#include "HealthPickup.h"
#include "Physics.h"
#include "AssetManager.h"

HealthPickup::HealthPickup()
	:Collectible()
{
	m_sprite.setTexture(AssetManager::RequestTexture("Assets/Powerups/Powerup_Health.png"));
	CollisionType::AABB;
}

HealthPickup::~HealthPickup()
{
}

void HealthPickup::Update(sf::Time _frameTime, sf::Vector2u levelSize)
{
	if (!Physics::GetAlive())
		return;

	m_position.x -= speed * _frameTime.asSeconds();
	m_sprite.setPosition(m_position);
}

void HealthPickup::Draw(sf::RenderTarget& target)
{
	if (!Physics::GetAlive())
		return;

	Physics::Draw(target);
}

void HealthPickup::Modify(int varInt)
{
	modValue = varInt;
}

bool HealthPickup::IsMarkedForDeletion() const
{
	return markedForDeletion;
}

void HealthPickup::SetMarkedForDeletion(bool value)
{
	markedForDeletion = value;
}

void HealthPickup::UpdatePosition(sf::Time _frameTime, sf::Vector2u levelSize)
{
	int minY = 0 + m_sprite.getGlobalBounds().height;
	int maxY = levelSize.y - m_sprite.getGlobalBounds().height;

	int minX = (levelSize.x / 7.0f) + m_sprite.getGlobalBounds().width;
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
