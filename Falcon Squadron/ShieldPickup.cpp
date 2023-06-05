#include "ShieldPickup.h"
#include "Physics.h"
#include "AssetManager.h"

ShieldPickup::ShieldPickup()
	:Collectible()
{
	m_sprite.setTexture(AssetManager::RequestTexture("Assets/Powerups/Powerup_Shields.png"));
	pickupID = 1;
	modValue = 25;
	CollisionType::AABB;
}

ShieldPickup::~ShieldPickup()
{
}

void ShieldPickup::Update(sf::Time _frameTime, sf::Vector2u levelSize)
{
	if (!Physics::GetAlive())
		return;

	m_position.x -= speed * _frameTime.asSeconds();
	m_sprite.setPosition(m_position);

	if (m_position.x < 0)
	{
		this->SetMarkedForDeletion(true);
	}
}

void ShieldPickup::Draw(sf::RenderTarget& target)
{
	if (!Physics::GetAlive())
		return;

	// Physics::Draw(target);

	target.draw(m_sprite);
}

int ShieldPickup::Modify()
{
	return modValue;
}

bool ShieldPickup::IsMarkedForDeletion() const
{
	return markedForDeletion;
}

void ShieldPickup::SetMarkedForDeletion(bool value)
{
	markedForDeletion = value;
}

sf::Clock ShieldPickup::GetAliveTime()
{
	return lifeCounter;
}

int ShieldPickup::GetPickupID()
{
	return pickupID;
}

void ShieldPickup::UpdatePosition(sf::Time _frameTime, sf::Vector2u levelSize)
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
