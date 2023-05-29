#pragma once
#include "EnemyShip.h"

class MediumShip :
    public EnemyShip
{
public:

    MediumShip();
    void Update(sf::Time frameTime, sf::Vector2u levelSize);
    void Draw(sf::RenderTarget& target);
   

protected:

private:
    void FireBullets();
    void DrawBullets(sf::RenderTarget& target);
    void UpdateBullets(sf::Time frameTime);

    void UpdatePosition(sf::Time frameTime, sf::Vector2u levelSize);


};
