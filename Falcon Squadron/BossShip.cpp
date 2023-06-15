#include "BossShip.h"
#include "AssetManager.h"
#include <cstdlib>

BossShip::BossShip()
    :EnemyShip()
{
    m_sprite.setTexture(AssetManager::RequestTexture("Assets/Enemy_01/Enemy01_Blue_Frame_1.png"));
    m_sprite.setRotation(90.f);
    m_speed = 250;
    m_health = 2000;
    m_score = 10000;
    m_damage = 40;

    shootCooldown = sf::seconds(1.f);
    m_CollisionOffset.x = -m_sprite.getLocalBounds().width;
}

void BossShip::Update(sf::Time frameTime, sf::Vector2u levelSize)
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

void BossShip::Draw(sf::RenderTarget& target)
{
    EnemyShip::Draw(target);
    DrawBullets(target);
}

int BossShip::GetDamage()
{
    return m_damage;
}

int BossShip::GetScore()
{
    return m_score;
}

void BossShip::SetHealth(int health)
{
    m_health -= health;
}

int BossShip::GetHealth()
{
    return m_health;
}

void BossShip::DeleteBullets()
{
    EnemyShip::DeleteBullets();

}

void BossShip::FireBullets()
{
    int spacer = 0;
    int spacer2 = 0;

    if (shootCooldownTimer.getElapsedTime() >= shootCooldown)
    {
        for (int i = 0; i < 10; ++i)
        {
            if (i == 0)
            {

                sf::Vector2f bulletPosition = m_sprite.getPosition();
                bulletPosition.y -= 35;
                bulletPosition.x -= 48;
                Bullet* newBullet = new Bullet(1000.f, m_damage, false, sf::seconds(10)); // Customize the bullet parameters as needed

                newBullet->SetPosition(bulletPosition);
                m_bullets.push_back(newBullet);
            }

            else if (i < 4)
            {
                sf::Vector2f bulletPosition = m_sprite.getPosition();
                bulletPosition.y -= 77 + spacer;
                bulletPosition.x -= 32;
                Bullet* newBullet = new Bullet(1000.f, m_damage, false, sf::seconds(10)); // Customize the bullet parameters as needed

                newBullet->SetPosition(bulletPosition);
                m_bullets.push_back(newBullet);

                spacer += 35;
            }

            else
            {
                sf::Vector2f bulletPosition = m_sprite.getPosition();
                bulletPosition.y -= 109 + spacer2;
                bulletPosition.x -= 16;
                Bullet* newBullet = new Bullet(1000.f, m_damage, false, sf::seconds(10)); // Customize the bullet parameters as needed

                newBullet->SetPosition(bulletPosition);
                m_bullets.push_back(newBullet);

                spacer2 += 35;
            }

        }


        
        shootCooldownTimer.restart(); // Restart the cooldown timer

    }
}

void BossShip::DrawBullets(sf::RenderTarget& target)
{
    for (int bullet = 0; bullet < m_bullets.size(); ++bullet)
    {
        m_bullets[bullet]->Draw(target); //draws the enemy  bullets. 
    }

}

void BossShip::UpdateBullets(sf::Time frameTime)
{
    for (auto& bullet : m_bullets)
    {
        bullet->Update(frameTime);  //updates the enemy bullets.
    }
}

void BossShip::UpdatePosition(sf::Time frameTime, sf::Vector2u levelSize)
{
    EnemyShip::UpdatePosition(frameTime, levelSize);
}

