#pragma once
#include "SpriteObject.h"
#include "Physics.h"
#include "Bullet.h"

class Player :
    public Physics
{
public:
    Player();

    void Update(sf::Time _frameTime, sf::Vector2u levelsize);

         
    void Draw(sf::RenderTarget& _target) override;
    void DrawBullets(sf::RenderTarget& _target);

    void FireBullets();

    void HandleCollision(Physics& other) override;
    void UpdatePosition(sf::Time frameTime, sf::Vector2u levelsize);

    void SetHealth(int newHealth);
    int GetHealth();

    void SetShields(int newShields);
    int GetShields();

    void UpdateSpeedBoost(sf::Time _frameTime);

protected:
    const int MAXSPEED;
    int speed;
    int speedBoosted;
    int shields;
    int health;
    
    float currentBoost;
    

private:

    std::vector<Bullet> bullets;
};
