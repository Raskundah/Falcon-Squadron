#include "Player.h"
#include "AssetManager.h"

Player::Player()
    :Physics()
    , health(100)
    , shields(0)
    , speed(500)
    , speedBoosted(1000)
    , MAXSPEED(2000)
    , currentBoost(0)
{
    m_sprite.setTexture(AssetManager::RequestTexture("Assets/Player/PlayerBlue_Frame_01.png"));
    m_sprite.setRotation(90.0f);
}



void Player::Update(sf::Time _frameTime, sf::Vector2u levelsize)
{


    UpdatePosition(_frameTime, levelsize);
    UpdateSpeedBoost(_frameTime);


}

void Player::Draw(sf::RenderTarget& _target)
{
	SpriteObject::Draw(_target);
}

void Player::HandleCollision(Physics& other)
{
	Physics::HandleCollision(other);
}

void Player::UpdatePosition(sf::Time frameTime, sf::Vector2u levelSize)
{
    // Update the player's position based on keyboard input

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        if (m_position.y + speed * frameTime.asSeconds() < levelSize.y - m_sprite.getLocalBounds().height - 32)
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
        if (m_position.x + speed * frameTime.asSeconds() < levelSize.x)
        {
            m_position.x += speed * frameTime.asSeconds();
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        if (m_position.x - speed * frameTime.asSeconds() >= 0 + m_sprite.getLocalBounds().width)
        {
            m_position.x -= speed * frameTime.asSeconds();
        }
    }

    m_sprite.setPosition(GetPosition());

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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && currentBoost > 0)
    {

        if (speedBoosted < MAXSPEED )
        {
            speedBoosted += 10 * _frameTime.asSeconds();
            speed += speedBoosted;
            currentBoost -= _frameTime.asSeconds();

            if (speedBoosted > speed )
            {
                speedBoosted = MAXSPEED;
                speed += speedBoosted;
            }
        }
    }
}
