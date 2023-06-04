#include "EnemyShip.h"
#include "AssetManager.h"
#include "LevelScreen.h"


EnemyShip::EnemyShip()
    : Physics()
    , m_health()
    , m_shields()
    , m_speed()
    , m_markedForDeletion(false)
    , m_bullets()
    , moveCooldown(sf::seconds(0.f))
    , shootCooldownTimer()
    , firstSpawn(true)
    , shootCooldown()
    , moveCooldownTimer()
    , moveDir()
    , m_damage()
{
    // Initialize the sprite, position, and other member variables
    // based on the specific variant of the enemy ship.
}

EnemyShip::~EnemyShip()
{
}

// EnemyShip::~EnemyShip() {}

void EnemyShip::Update(sf::Time frameTime, sf::Vector2u levelSize)
{
    if (!Physics::GetAlive())
        return;

    UpdatePosition(frameTime, levelSize);
    FireBullets();
    UpdateBullets(frameTime);

}

void EnemyShip::Draw(sf::RenderTarget& target)
{
    if (!Physics::GetAlive())
        return;

    Physics::Draw(target);

    // target.draw(m_sprite);
    //Draw other visual elements associated with the enemy ship.

}

int EnemyShip::GetHealth()
{
    return m_health;
}

void EnemyShip::SetHealth(int health)
{
    m_health = health;
}

void EnemyShip::HandleCollision(Physics& other)
{
    Physics::HandleCollision(other);
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

int EnemyShip::getRandomDirection()
{
    // Create a random number generator engine
    std::random_device rd;
    std::mt19937 gen(rd());

    // Create a distribution to generate either 1 or -1
    std::uniform_int_distribution<int> distribution(0, 1);

    // Generate and return a random number (either 1 or -1)
    return (distribution(gen) == 0) ? -1 : 1;
}

void EnemyShip::UpdatePosition(sf::Time frameTime, sf::Vector2u levelSize)
{


     //create ranges for random positions within defined bounds, taking the window size as paramaters.
    int minY = 0 + m_sprite.getGlobalBounds().height;
    int maxY = levelSize.y - m_sprite.getGlobalBounds().height;

    int minX = (levelSize.x * 0.5f) + m_sprite.getGlobalBounds().width;
    int maxX = levelSize.x - m_sprite.getGlobalBounds().width;

    int rangeY = maxY - minY;
    int rangeX = maxX - minX;

    bool direction;

    if (firstSpawn)
    {
      
        m_position.y = rand() % rangeY;

        m_position.x = rand() % rangeX + minX;

        moveDir = getRandomDirection();

        firstSpawn = false;

    }


    if (moveCooldownTimer.getElapsedTime() >= moveCooldown)
    {
      


        if (moveDir == 1)
        {
            m_position.y += m_speed * frameTime.asSeconds();

        }

        if (moveDir == -1)
        {
            m_position.y -= m_speed * frameTime.asSeconds();

        }

        
        if (m_position.y >= levelSize.y * 0.99f)
        {
            m_position.y  = levelSize.y - m_sprite.getGlobalBounds().height;

            // we have hit the bottom of the screen, change direction.
            moveDir = -1;
        }

        if (m_position.y <= 0 + m_sprite.getGlobalBounds().height)
        {
            m_position.y = m_sprite.getGlobalBounds().height;
            moveDir = 1;

            // we have hit the top of the screen, change direction.
        }
        
        m_sprite.setPosition(m_position);
    }
}

void EnemyShip::UpdateBullets(sf::Time frameTime)
{
    // Update the position and other properties of the bullets fired by the enemy ship
    // This can vary depending on the variant of the enemy ship
}

