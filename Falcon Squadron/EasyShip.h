#pragma once
#include "EnemyShip.h"

class EasyShip :
    public EnemyShip
{
public:

    EasyShip();
    void Update(sf::Time frameTime, sf::Vector2u levelSize);
    void Draw(sf::RenderTarget& target);
    int GetDamage();
    int GetScore();
    void DeleteBullets();

    void SetHealth(int health);
    int GetHealth();

protected:

private:
    void FireBullets();
    void DrawBullets(sf::RenderTarget& target);
    void UpdateBullets(sf::Time frameTime);

    void UpdatePosition(sf::Time frameTime, sf::Vector2u levelSize);


};

