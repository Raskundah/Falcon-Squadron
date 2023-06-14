#include "Player.h"
#include "AssetManager.h"

Player::Player() // player contructor 
    : Physics()
    , health(100)
    , damage(25)
    , shields(0)
    , maxHealth(100)
    , MaxShields(100)
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
    m_CollisionOffset.x = -m_sprite.getLocalBounds().width;

    bulletCooldown = sf::seconds(0.5f); //defining the players shooting cooldown. 

    collisionType = CollisionType::AABB;
}

void Player::Update(sf::Time _frameTime, sf::Vector2u levelsize)
{
    if (!Physics::GetAlive())
        return;

    UpdatePosition(_frameTime, levelsize);
    UpdateSpeedBoost(_frameTime);
    FireBullets();
    UpdateBullets(_frameTime);
    DeleteBullets();
    ExploitHandler(levelsize);
    
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](const Bullet* bullet) {
        return bullet->IsMarkedForDeletion();
        }), bullets.end());
        
}

void Player::Draw(sf::RenderTarget& _target)
{
    if (!Physics::GetAlive())
        return;

    //Physics::Draw(_target);

     _target.draw(m_sprite);; //Draws the player object.
    DrawBullets(_target);
}

void Player::DrawBullets(sf::RenderTarget& _target)
{
    for (int bullet = 0; bullet < bullets.size(); ++bullet)
    {
        bullets[bullet]->Draw(_target); //draws the players bullets. 
    }
}

void Player::UpdateBullets(sf::Time _frameTime)
{
    for (int bullet = 0; bullet < bullets.size(); ++bullet)
    {
     
        bullets[bullet]->Update(_frameTime); //draws the players bullets. 
    }
}

void Player::DeleteBullets()
{
    for (int i = bullets.size() - 1; i >= 0; --i)
    {
        // If anything else is to be done, do it before the delete call
        if (bullets[i]->IsMarkedForDeletion())
        {
            delete bullets[i];
           bullets.erase(bullets.begin() + i);
        }// Do NOT do anything else in the loop after this as it will break!
    }
}

void Player::FireBullets() //generates a bullet to the players bullet vector and handles the initilisation of each.
 {
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4)) && cooldownTimer.getElapsedTime() >= bulletCooldown)
    {
        sf::Vector2f bulletPosition = m_sprite.getPosition(); 
        bulletPosition.y += m_sprite.getLocalBounds().height * 0.5f; // Adjust x-coordinate to the right side of the player

        Bullet* newBullet = new Bullet(1000.f, 10, true, sf::seconds(10)); // Customize the bullet parameters as needed
        // newBullet.SetSpriteTexture(AssetManager::RequestTexture("Assets/Bullets/Proton_Medium.png"));
        newBullet->SetPosition(bulletPosition);
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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        if (m_position.y + speed * frameTime.asSeconds() < levelSize.y - m_sprite.getLocalBounds().height - 32)
        {
            m_position.y += speed * frameTime.asSeconds();
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        if (m_position.y - speed * frameTime.asSeconds() >= 0)
        {
            m_position.y -= speed * frameTime.asSeconds();
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        if (m_position.x + speed * frameTime.asSeconds() < levelSize.x)
        {
            m_position.x += speed * frameTime.asSeconds();
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)|| sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
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
    health += newHealth;
    if (health >= maxHealth)
    {
        health = maxHealth;
    }
}

int Player::GetHealth()
{
    return health;
}

void Player::DestroyAllBullets()
{
    for (int i = bullets.size() - 1; i >= 0; --i)
    {
            delete bullets[i];
    }
    bullets.clear();
}

std::vector<Bullet*> Player::GetBullets()
{
    return bullets;
}


void Player::SetShields(int newShields)
{
    shields += newShields;

    if (shields >= MaxShields)
    {
        shields = MaxShields;
    }

    if (shields <= 0)
    {
        health += shields;
        shields = 0;
    }
}

int Player::GetShields()
{
    return shields;
}

int Player::GetDamage()
{
    return damage;
}

int Player::GetScore()
{
    return score;
}

void Player::SetScore(int scoreToAdd)
{
    score += scoreToAdd;
}

void Player::ResetScore()
{
    score = 0;
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

bool Player::ExploitHandler(sf::Vector2u levelSize)
{


    {
        if (exploitTimer.getElapsedTime().asSeconds() > 1.0f)
        {
            exploitTimer.restart();
            return hasBeenDamaged == true;
        }
    }
    if (m_sprite.getPosition().x > levelSize.x * 0.75)
        SetHealth(-10);
    return hasBeenDamaged == false;
    
}

void Player::SetExploitChecker(bool _pain)
{
    hasBeenDamaged = _pain;
}
