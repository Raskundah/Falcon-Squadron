
#include "EasyShip.h"
#include "AssetManager.h"
#include <cstdlib>

EasyShip::EasyShip()
    :EnemyShip()
{
    m_sprite.setTexture(AssetManager::RequestTexture("Assets/Enemy_02/Enemy02_Blue_Frame_1.png"));
    m_sprite.setRotation(90.f);
    m_speed = 750;
    shootCooldown = sf::seconds(0.2f);


}

void EasyShip::Update(sf::Time frameTime, sf::Vector2u levelSize)
{
    UpdatePosition(frameTime, levelSize);
    FireBullets();
    UpdateBullets(frameTime);

    // Remove bullets that are marked for deletion
    m_bullets.erase(std::remove_if(m_bullets.begin(), m_bullets.end(), [](const Bullet& bullet) {
        return bullet.IsMarkedForDeletion();
        }), m_bullets.end());
}

void EasyShip::Draw(sf::RenderTarget& target)
{
    EnemyShip::Draw(target);
    DrawBullets(target);
}

void EasyShip::FireBullets()
{


    if (shootCooldownTimer.getElapsedTime() >= shootCooldown)
    {
        sf::Vector2f bulletPosition = m_sprite.getPosition();
        bulletPosition.y -= 35;
        bulletPosition.x -= 16;
        Bullet newBullet(500.f, 5, false, sf::seconds(5)); // Customize the bullet parameters as needed

        newBullet.SetPosition(bulletPosition);
        m_bullets.push_back(newBullet);


        shootCooldownTimer.restart(); // Restart the cooldown timer
    }
}

void EasyShip::DrawBullets(sf::RenderTarget& target)
{
    for (int bullet = 0; bullet < m_bullets.size(); ++bullet)
    {
        m_bullets[bullet].Draw(target); //draws the enemy  bullets. 
    }

    /*for (auto& bullet : m_bullets)
    {
        bullet.Draw(target); // Draw each bullet
    }

    */
}

void EasyShip::UpdateBullets(sf::Time frameTime)
{
    for (auto& bullet : m_bullets)
    {
        bullet.Update(frameTime);  //updates the enemy bullets.
    }
}

void EasyShip::UpdatePosition(sf::Time frameTime, sf::Vector2u levelSize)
{
    EnemyShip::UpdatePosition(frameTime, levelSize);
}
