#include "ChallengingShip.h"
#include "AssetManager.h"
#include <cstdlib>

ChallengingShip::ChallengingShip()
    :EnemyShip()
{
    m_sprite.setTexture(AssetManager::RequestTexture("Assets/Enemy_01/Enemy01_Red_Frame_1.png"));
    m_sprite.setRotation(90.f);
    m_speed = 250;
    m_health = 200;
    m_score = 1000;
    m_damage = 25;
    
    shootCooldown = sf::seconds(1.f);
    m_CollisionOffset.x = -m_sprite.getLocalBounds().width;
}

void ChallengingShip::Update(sf::Time frameTime, sf::Vector2u levelSize)
{
    UpdatePosition(frameTime, levelSize);
    FireBullets();
    UpdateBullets(frameTime);
    DeleteBullets();

    if (m_health <= 0)
    {
        SetMarkedForDeletion(true);
    }

    // Remove bullets that are marked for deletion
    m_bullets.erase(std::remove_if(m_bullets.begin(), m_bullets.end(), [](const Bullet* bullet) {
        return bullet->IsMarkedForDeletion();
        }), m_bullets.end());
}

void ChallengingShip::Draw(sf::RenderTarget& target)
{
    EnemyShip::Draw(target);
    DrawBullets(target);
}

int ChallengingShip::GetDamage()
{
    return m_damage;
}

int ChallengingShip::GetScore()
{
    return m_score;
}

void ChallengingShip::SetHealth(int health)
{
    m_health -= health;
}

int ChallengingShip::GetHealth()
{
    return m_health;
}

void ChallengingShip::DeleteBullets()
{
    EnemyShip::DeleteBullets();

}

void ChallengingShip::FireBullets()
{
    if (shootCooldownTimer.getElapsedTime() >= shootCooldown)
    {
        sf::Vector2f bulletPosition = m_sprite.getPosition();
        bulletPosition.y -= 35;
        bulletPosition.x -= 16;
        Bullet* newBullet = new Bullet(1000.f, m_damage, false, sf::seconds(5)); // Customize the bullet parameters as neede

        newBullet->SetPosition(bulletPosition);
        m_bullets.push_back(newBullet);

        shootCooldownTimer.restart(); // Restart the cooldown timer
    }
}

void ChallengingShip::DrawBullets(sf::RenderTarget& target)
{
    for (int bullet = 0; bullet < m_bullets.size(); ++bullet)
    {
        m_bullets[bullet]->Draw(target); //draws the enemy  bullets. 
    }

}

void ChallengingShip::UpdateBullets(sf::Time frameTime)
{
    for (auto& bullet : m_bullets)
    {
        bullet->Update(frameTime);  //updates the enemy bullets.
    }
}

void ChallengingShip::UpdatePosition(sf::Time frameTime, sf::Vector2u levelSize)
{
    EnemyShip::UpdatePosition(frameTime, levelSize);
}
