#include "Player.h"
#include "AssetManager.h"

Player::Player()
    :Physics()
    , health(100)
    , shields(0)
    , speed(50)
    , speedBoosted(100)
    , MAXSPEED(100)
    , currentBoost(100)
{
    m_sprite.setTexture(AssetManager::RequestTexture("Assets/Player/PlayerBlue_Frame_01.png"));
}


void Player::Update(sf::Time _frameTime)
{
}

void Player::Update(sf::Time _frameTime)
{
    UpdatePosition(_frameTime);
    UpdateSpeedBoost(_frameTime);

}

void Player::Draw(sf::RenderTarget& _target)
{
	Physics::Draw(_target);
}

void Player::HandleCollision(Physics& other)
{
	Physics::HandleCollision(other);
}

void Player::UpdatePosition(sf::Time frameTime, const sf::Vector2u& screenSize)
{
    // Update the player's position based on keyboard input

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        if (m_position.y + speed * frameTime.asSeconds() < screenSize.y)
        {
            m_position.y += speed * frameTime.asSeconds();
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        if (m_position.y - speed * frameTime.asSeconds() >= 0)
        {
            m_position.y -= speed * frameTime.asSeconds();
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        if (m_position.x + speed * frameTime.asSeconds() < screenSize.x)
        {
            m_position.x += speed * frameTime.asSeconds();
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        if (m_position.x - speed * frameTime.asSeconds() >= 0)
        {
            m_position.x -= speed * frameTime.asSeconds();
        }
    }
}

void Player::SetHealth(int newHealth)
{
    health = newHealth;
}

int Player::GetHealth()
{
    return health;
}


void Player::SetShields(int newShields)
{
    shields = newShields;
}

int Player::GetShields()
{
    return shields;;
}



void Player::UpdateSpeedBoost(sf::Time _frameTime)
{
    // Update the speed boost value

   // Increment the speed boost by 10 per second until it reaches the maximum boost value

    if (speedBoosted < MAXSPEED && currentBoost > 0)
    {
        speedBoosted += 10 * _frameTime.asSeconds();
        speed += speedBoosted;
        currentBoost -= _frameTime.asSeconds();

        if (speedBoosted > speed && currentBoost > 0)
        {
            speedBoosted = MAXSPEED;
            speed += speedBoosted;
        }
    }
}
