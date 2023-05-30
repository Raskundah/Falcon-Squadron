#include "Player.h"
#include "AssetManager.h"

Player::Player() // player contructor 
    : Physics()
    , health(100)
    , shields(0)
    , speed(500)
    , speedBoosted(1000)
    , MAXSPEED(2000)
    , currentBoost(0)
    , bullets()
    , bulletCooldown()
    , cooldownTimer()
{
    m_sprite.setTexture(AssetManager::RequestTexture("Assets/Player/PlayerBlue_Frame_01.png"));
    m_sprite.setRotation(90.0f); //rotates the sprite to suit our needs.

    bulletCooldown = sf::seconds(0.2); //defining the players shooting cooldown. 
}

void Player::Update(sf::Time _frameTime, sf::Vector2u levelsize)
{

    UpdatePosition(_frameTime, levelsize);
    UpdateSpeedBoost(_frameTime);
    FireBullets();
    UpdateBullets(_frameTime);


    // Remove bullets that are marked for deletion
    /*
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](const Bullet& bullet) {
        return bullet.IsMarkedForDeletion();
        }), bullets.end());
        */
}

void Player::Draw(sf::RenderTarget& _target)
{
	SpriteObject::Draw(_target); //Draws the player object.
    DrawBullets(_target);
}

void Player::DrawBullets(sf::RenderTarget& _target)
{
    for (int bullet = 0; bullet < bullets.size(); ++bullet)
    {
        bullets[bullet].Draw(_target); //draws the players bullets. 
    }
}

void Player::UpdateBullets(sf::Time _frameTime)
{
    for (int bullet = 0; bullet < bullets.size(); ++bullet)
    {
        bullets[bullet].Update(_frameTime); //draws the players bullets. 
    }
}

void Player::FireBullets() //generates a bullet to the players bullet vector and handles the initilisation of each.
 {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && cooldownTimer.getElapsedTime() >= bulletCooldown)
    {
        sf::Vector2f bulletPosition = m_sprite.getPosition(); 
        bulletPosition.y += m_sprite.getLocalBounds().height * 0.5f; // Adjust x-coordinate to the right side of the player

        Bullet newBullet(500.f, 10, true, sf::seconds(5)); // Customize the bullet parameters as needed
        // newBullet.SetSpriteTexture(AssetManager::RequestTexture("Assets/Bullets/Proton_Medium.png"));
        newBullet.SetPosition(bulletPosition);
        bullets.push_back(newBullet); 

        cooldownTimer.restart(); // Restart the cooldown timer
    }
}

void Player::HandleCollision(Physics& other)
{
	Physics::HandleCollision(other); //impliments the physics collision.
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

std::vector<Bullet> Player::GetBullets()
{
    return bullets;
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
