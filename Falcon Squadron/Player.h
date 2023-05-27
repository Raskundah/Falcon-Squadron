#pragma once
#include "SpriteObject.h"
#include "Physics.h"

class Player :
    public Physics
{
public:
    Player();

    void Update(sf::Time _frameTime) override;
         
    void Draw(sf::RenderTarget& _target) override;

    void HandleCollision(Physics& other) override;
    void UpdatePosition(sf::Time frameTime);

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

};
