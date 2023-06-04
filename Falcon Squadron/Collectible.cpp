#include "Collectible.h"

Collectible::Collectible()
	: speed(300)
	, modValue()
	, firstSpawn(true)
	, lifeTime(sf::seconds(10.0f))
	,pickupID()
{

}

Collectible::~Collectible()
{

}

void Collectible::Update(sf::Time _frameTime, sf::Vector2u levelSize)
{	

}

void Collectible::Draw(sf::RenderTarget& target)
{
	//Physics::Draw(target);
}

bool Collectible::IsMarkedForDeletion() const
{
	return false;
}

void Collectible::SetMarkedForDeletion(bool value)
{

}

sf::Clock Collectible::GetAliveTime()
{
	 return sf::Clock();
}

void Collectible::UpdatePosition(sf::Time _frameTime, sf::Vector2u levelSize)
{
	m_sprite.setPosition(GetPosition());
}
