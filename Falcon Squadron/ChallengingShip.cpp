#include "ChallengingShip.h"
#include "AssetManager.h"
#include <cstdlib>

ChallengingShip::ChallengingShip()
    :EnemyShip()
{
    m_sprite.setTexture(AssetManager::RequestTexture("Assets/Enemy_01/Enemy01_Red_Frame_1.png"));
    m_sprite.setRotation(90.f);
    m_speed = 250;
    shootCooldown = sf::seconds(1.f);


}

void ChallengingShip::Update(sf::Time frameTime, sf::Vector2u levelSize)
{
    UpdatePosition(frameTime, levelSize);
    FireBullets();
    UpdateBullets(frameTime);

    // Remove bullets that are marked for deletion
    m_bullets.erase(std::remove_if(m_bullets.begin(), m_bullets.end(), [](const Bullet& bullet) {
        return bullet.IsMarkedForDeletion();
        }), m_bullets.end());
}

void ChallengingShip::Draw(sf::RenderTarget& target)
{
    EnemyShip::Draw(target);
    DrawBullets(target);
}

void ChallengingShip::FireBullets()
{


    if (shootCooldownTimer.getElapsedTime() >= shootCooldown)
    {
        sf::Vector2f bulletPosition = m_sprite.getPosition();
        bulletPosition.y -= 35;
        bulletPosition.x -= 16;
        Bullet newBullet(1000.f, 20, false, sf::seconds(5)); // Customize the bullet parameters as neede

        newBullet.SetPosition(bulletPosition);
        m_bullets.push_back(newBullet);

        shootCooldownTimer.restart(); // Restart the cooldown timer
    }
}

void ChallengingShip::DrawBullets(sf::RenderTarget& target)
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

void ChallengingShip::UpdateBullets(sf::Time frameTime)
{
    for (auto& bullet : m_bullets)
    {
        bullet.Update(frameTime);  //updates the enemy bullets.
    }
}

void ChallengingShip::UpdatePosition(sf::Time frameTime, sf::Vector2u levelSize)
{
    EnemyShip::UpdatePosition(frameTime, levelSize);
}
