#include "EnemyShip.h"

EnemyShip::EnemyShip()
    : m_health()
    , m_shields()
    , m_speed(500.0f)
    , m_markedForDeletion(false)
    , m_bullets()
{
    // Initialize the sprite, position, and other member variables
    // based on the specific variant of the enemy ship.
}

EnemyShip::~EnemyShip() {}

void EnemyShip::Update(sf::Time frameTime, sf::Vector2u levelSize)
{
    UpdatePosition(frameTime, levelSize);
    UpdateBullets(frameTime);
}

void EnemyShip::Draw(sf::RenderTarget& target)
{
    target.draw(m_sprite);
    // Draw other visual elements associated with the enemy ship.
}

void EnemyShip::FireBullet()
{
    // Create a new bullet and set its properties based on the enemy variant
   // Bullet newBullet(50.0f,  false, sf::seconds(10));
    //newBullet.SetPosition(m_sprite.getPosition());
   // m_bullets.push_back(newBullet);
}

bool EnemyShip::IsMarkedForDeletion() const
{
    return m_markedForDeletion;
}

void EnemyShip::SetMarkedForDeletion(bool value)
{
    m_markedForDeletion = value;
}

void EnemyShip::UpdatePosition(sf::Time frameTime, sf::Vector2u levelSize)
{
    // Update the enemy ship's position based on its movement logic
    // This can vary depending on the variant of the enemy ship
}

void EnemyShip::UpdateBullets(sf::Time frameTime)
{
    // Update the position and other properties of the bullets fired by the enemy ship
    // This can vary depending on the variant of the enemy ship
}