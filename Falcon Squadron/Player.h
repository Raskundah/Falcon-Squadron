#pragma once
#include "SpriteObject.h"
#include "Physics.h"
#include "Bullet.h"

class Bullet;

class Player :
    public Physics
    
{
public:
    Player();

    void Update(sf::Time _frameTime, sf::Vector2u levelsize);

         
    void Draw(sf::RenderTarget& _target) override; //draws the player
    void DrawBullets(sf::RenderTarget& _target); //draws the player's bullets
    void UpdateBullets(sf::Time _frameTime); //updates players bullets
    void DeleteBullets(); //deletes bullets marked for deletion.

    void FireBullets(); // generates the bullets and fires them.

    void HandleCollision(Physics& other) override; //handles collision, currently working.
    void UpdatePosition(sf::Time frameTime, sf::Vector2u levelsize); //updates the player's position

    void SetHealth(int newHealth); // sets the players health
    int GetHealth(); //gets the players health

    std::vector<Bullet*> GetBullets(); //Idk why I did it this way, but it works, this returns the player's vector of bullets. May need to make this private LOL NO.

    void SetShields(int newShields);  //sets the players shields when colliding with an item that affects the shields.
    int GetShields(); // gets the players shields. 

    int GetDamage(); // gets incoming damage to be dealt to the player. technically we can use the set health function and take a minus value.

    int GetScore(); // gets the players score. 
    void SetScore(int scoreToAdd); // adds to score.

    void UpdateSpeedBoost(sf::Time _frameTime); //handles the players speed boost. This logic hasn't been properly tested yet.

protected:
    const int MAXSPEED;
    int speed;
    int speedBoosted;
    int shields;
    int maxHealth;
    int MaxShields;
    int health;
    int damage;
    int score;

    float currentBoost;
    std::vector<Bullet*> bullets;

private:
    sf::Time bulletCooldown;
    sf::Clock cooldownTimer;
};
