#pragma once

#include <SFML/Graphics.hpp>
#include "Bullet.h"

class EnemyShip :
    public Physics
{
    
public:
    EnemyShip();
    virtual ~EnemyShip();

    void Update(sf::Time frameTime, sf::Vector2u levelSize);
    void Draw(sf::RenderTarget& target);

    void HandleCollision(Physics& other);

    virtual void FireBullet();

    bool IsMarkedForDeletion() const;
    void SetMarkedForDeletion(bool value);
    std::vector<Bullet> GetBullets();

protected:
    int m_health;
    int m_shields;
    float m_speed;
    std::vector<Bullet> m_bullets;
    bool m_markedForDeletion;

    virtual void UpdatePosition(sf::Time frameTime, sf::Vector2u levelSize);
    virtual void UpdateBullets(sf::Time frameTime);
    sf::Time moveCooldown;
    sf::Time shootCooldown;
    sf::Clock moveCooldownTimer;
    sf::Clock shootCooldownTimer;

    bool firstSpawn;
};