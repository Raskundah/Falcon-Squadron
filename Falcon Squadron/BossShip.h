#pragma once
#include "EnemyShip.h"

class BossShip :
    public EnemyShip
{
public:

    BossShip();
    void Update(sf::Time frameTime, sf::Vector2u levelSize);
    void Draw(sf::RenderTarget& target);

    int GetDamage();
    int GetScore();

    void SetHealth(int health);
    int GetHealth();
    void DeleteBullets();

protected:

private:
    void FireBullets();
    void DrawBullets(sf::RenderTarget& target);
    void UpdateBullets(sf::Time frameTime);

    void UpdatePosition(sf::Time frameTime, sf::Vector2u levelSize);


};
