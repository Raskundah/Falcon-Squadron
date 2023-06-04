
#include "MediumShip.h"
#include "AssetManager.h"
#include <cstdlib>

MediumShip::MediumShip()
	: EnemyShip()

{
    m_sprite.setTexture(AssetManager::RequestTexture("Assets/Player/Green_Frame_01.png"));
    m_sprite.setRotation(270.f);
    m_speed = 500;
    m_health = 100;
    m_damage = 10;
    shootCooldown = sf::seconds(1.0f);
    m_CollisionOffset.y = -m_sprite.getLocalBounds().height;


}

void MediumShip::Update(sf::Time frameTime, sf::Vector2u levelSize)
{
    UpdatePosition(frameTime, levelSize);
    FireBullets();
    UpdateBullets(frameTime);

    if (m_health <= 0)
    {
        this->SetMarkedForDeletion(true);
    }

    // Remove bullets that are marked for deletion
    m_bullets.erase(std::remove_if(m_bullets.begin(), m_bullets.end(), [](const Bullet& bullet) {
        return bullet.IsMarkedForDeletion();
        }), m_bullets.end());
}

void MediumShip::Draw(sf::RenderTarget& target)
{
    EnemyShip::Draw(target);
    DrawBullets(target);
}

int MediumShip::GetDamage()
{
    return m_damage;
}

void MediumShip::SetHealth(int health)
{
    m_health -= health;
}

int MediumShip::GetHealth()
{
    return m_health;
}

void MediumShip::FireBullets()
{
   

    if (shootCooldownTimer.getElapsedTime() >= shootCooldown)
    {
        sf::Vector2f bulletPosition = m_sprite.getPosition();
        bulletPosition.y -= 35;
        bulletPosition.x -= 16;
        Bullet newBullet(500.f, m_damage, false, sf::seconds(5)); // Customize the bullet parameters as neede

        newBullet.SetPosition(bulletPosition);
        m_bullets.push_back(newBullet);

        shootCooldownTimer.restart(); // Restart the cooldown timer
    }
}

void MediumShip::DrawBullets(sf::RenderTarget& target)
{
    for (int bullet = 0; bullet < m_bullets.size(); ++bullet)
    {
        m_bullets[bullet].Draw(target); //draws the enemy bullets. 
    }

    /*for (auto& bullet : m_bullets)
    {
        bullet.Draw(target); // Draw each bullet
    }

    */
}

void MediumShip::UpdateBullets(sf::Time frameTime)
{
    for (auto& bullet : m_bullets)
    {
        bullet.Update(frameTime);  //updates the enemy bullets.
    }
}

void MediumShip::UpdatePosition(sf::Time frameTime, sf::Vector2u levelSize)
{
    EnemyShip::UpdatePosition(frameTime, levelSize);
}
