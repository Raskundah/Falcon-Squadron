#include "Bullet.h"
#include "AssetManager.h"

Bullet::Bullet(float _speed, int _damage, bool _isPlayerFired)
	: Physics()
	, speed(_speed)
	, damage(_damage)
	, isPlayerFired(_isPlayerFired)
{
	m_sprite.setTexture(AssetManager::RequestTexture("Assets/Bullets/Proton_Medium.png"));
}
void Bullet::Update(sf::Time frameTime)
{
	SetBulletPath(frameTime);
}

void Bullet::SetDamage(int _damage)
{
	this->damage = _damage;
}

void Bullet::SetBulletPath(sf::Time _frameTime)
{
	// Update bullet position based on its movement logic
	sf::Vector2f movement(0.f, -speed * _frameTime.asSeconds());

	if (isPlayerFired)
	{
		// Move bullet from left to right for the player
		movement.x = speed * _frameTime.asSeconds();
	}
	else
	{
		// Move bullet from right to left for enemies
		movement.x = -speed * _frameTime.asSeconds();
	}

	m_sprite.setPosition(movement);
}