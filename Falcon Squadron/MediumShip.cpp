
#include "MediumShip.h"
#include "AssetManager.h"
#include <cstdlib>

MediumShip::MediumShip()
	:EnemyShip()
{
    m_sprite.setTexture(AssetManager::RequestTexture("Assets/Player/Green_Frame_01.png"));
    m_sprite.setRotation(270.f);
    m_speed = 50;
    shootCooldown = sf::seconds(0.1f);
    

}

void MediumShip::Update(sf::Time frameTime, sf::Vector2u levelSize)
{
    UpdatePosition(frameTime, levelSize);
    FireBullets();
    UpdateBullets(frameTime);

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

void MediumShip::FireBullets()
{
    if (cooldownTimer.getElapsedTime() >= shootCooldown)
    {
        sf::Vector2f bulletPosition = m_sprite.getPosition();
        //bulletPosition.y -= m_sprite.getLocalBounds().height; // Adjust x-coordinate to the right side of the enemy
        // bulletPosition.x -= 10;
        Bullet newBullet(500.f, 10, false, sf::seconds(5)); // Customize the bullet parameters as needed

        newBullet.SetPosition(bulletPosition);
        m_bullets.push_back(newBullet);

        cooldownTimer.restart(); // Restart the cooldown timer
    }
}

void MediumShip::DrawBullets(sf::RenderTarget& target)
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
