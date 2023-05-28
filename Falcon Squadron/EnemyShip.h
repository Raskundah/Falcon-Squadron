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

    virtual void FireBullet() = 0;

    bool IsMarkedForDeletion() const;
    void SetMarkedForDeletion(bool value);

protected:
    int m_health;
    int m_shields;
    float m_speed;
    std::vector<Bullet> m_bullets;
    bool m_markedForDeletion;

    void UpdatePosition(sf::Time frameTime, sf::Vector2u levelSize);
    void UpdateBullets(sf::Time frameTime);
};