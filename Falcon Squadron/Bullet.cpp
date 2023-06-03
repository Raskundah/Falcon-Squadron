#include "Bullet.h"
#include "AssetManager.h"


Bullet::Bullet(float _speed, int _damage, bool _isPlayerFired, sf::Time _lifetime)
	: Physics()
	, speed(_speed)
	, damage(_damage)
	, isPlayerFired(_isPlayerFired)
	, lifetime(_lifetime)
	, markedForDeletion(false)
{
	m_sprite.setTexture((AssetManager::RequestTexture("Assets/Bullets/Proton_Medium.png")));
	//collisionType = CollisionType::CIRCLE;

	lifetimeTimer.restart();
}


void Bullet::Update(sf::Time frameTime)
{

	if (lifetimeTimer.getElapsedTime() >= lifetime) 
	{
		// Mark the bullet for deletion
		SetMarkedForDeletion(true);
		return;
	}

	SetBulletPath(frameTime);	
}

void Bullet::Draw(sf::RenderTarget& _target)
{
	//_target.draw(m_sprite);
	Physics::Draw(_target);
}

bool Bullet::IsMarkedForDeletion() const
{
	return markedForDeletion;
}

void Bullet::SetMarkedForDeletion(bool value)
{
	markedForDeletion = value;
}

void Bullet::SetDamage(int _damage)
{
	damage = _damage;
}

	void Bullet::SetBulletPath(sf::Time _frameTime)
	{
		

if (isPlayerFired)
	{
		// Move bullet from left to right for the player
		m_position.x += speed * _frameTime.asSeconds();
	}
	else
	{
		// Move bullet from right to left for enemies
		m_position.x += -speed * _frameTime.asSeconds();
	}

	m_sprite.setPosition(GetPosition());
	}

	void Bullet::SetSpriteTexture(sf::Texture i_bullet)
	{
		m_sprite.setTexture(i_bullet);
	}

	bool Bullet::GetShooter()
	{
		return isPlayerFired;
	}
