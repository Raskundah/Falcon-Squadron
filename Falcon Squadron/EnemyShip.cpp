#include "EnemyShip.h"
#include "AssetManager.h"

EnemyShip::EnemyShip()
    : Physics()
    , m_health()
    , m_shields()
    , m_speed()
    , m_markedForDeletion(false)
    , m_bullets()
    , moveCooldown(sf::seconds(1.0f))
    , shootCooldownTimer()
    , firstSpawn(true)
    , shootCooldown()
    , moveCooldownTimer()
{
    // Initialize the sprite, position, and other member variables
    // based on the specific variant of the enemy ship.

    srand(time(NULL));

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

void EnemyShip::HandleCollision(Physics& other)
{
    Physics::HandleCollision(other);
}

void EnemyShip::FireBullet()
{

}

bool EnemyShip::IsMarkedForDeletion() const
{
    return m_markedForDeletion;
}

void EnemyShip::SetMarkedForDeletion(bool value)
{
    m_markedForDeletion = value;
}

std::vector<Bullet> EnemyShip::GetBullets()
{
    return m_bullets;
}

void EnemyShip::UpdatePosition(sf::Time frameTime, sf::Vector2u levelSize)
{
    if (firstSpawn)
    {
        m_position.y = levelSize.y / 3.0f;
        firstSpawn = false;
    }

    if (moveCooldownTimer.getElapsedTime() >= moveCooldown)
    {
        // Randomly change the y-axis position within a range
        int randomY = rand() % 3 - 1; // Generate random number between -1 and 1
        m_position.y += randomY * m_speed * frameTime.asSeconds();

        // Keep the x-axis position within a specific range
        // Adjust the minimum and maximum values as needed
        const float minX = levelSize.x / 2.0f;
        const float maxX = levelSize.x;
       // m_position.x = std::max(minX, std::min(maxX, m_position.x));
        m_position.x = rand() % (levelSize.x) + levelSize.x;



        
        if (m_position.y + m_speed * frameTime.asSeconds() < levelSize.y - m_sprite.getLocalBounds().height - 32)
        {
            m_position.y += m_speed * frameTime.asSeconds();
        }

        if (m_position.y - m_speed * frameTime.asSeconds() >= 0)
        {
            m_position.y -= m_speed * frameTime.asSeconds();
        }
        
        m_sprite.setPosition(GetPosition());
        moveCooldownTimer.restart();
    }
}

void EnemyShip::UpdateBullets(sf::Time frameTime)
{
    // Update the position and other properties of the bullets fired by the enemy ship
    // This can vary depending on the variant of the enemy ship
}