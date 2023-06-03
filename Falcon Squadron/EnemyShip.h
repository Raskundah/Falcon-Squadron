#pragma once

#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include <random>


class EnemyShip :
    public Physics
{
    
public:
    EnemyShip();
    virtual ~EnemyShip();

    void Update(sf::Time frameTime, sf::Vector2u levelSize); //update base function for all ships
    void Draw(sf::RenderTarget& target); //draw base function for all ships

    virtual void FireBullets() = 0; 
    int GetHealth();
    void SetHealth(int health);

    void HandleCollision(Physics& other); // default collision call for all ships

    virtual void UpdatePosition(sf::Time frameTime, sf::Vector2u levelSize);
    virtual void UpdateBullets(sf::Time frameTime) = 0;

    bool IsMarkedForDeletion() const; // checks if a ship is marked for deletion
    void SetMarkedForDeletion(bool value); // sets a ship to be marked for deletion.
    std::vector<Bullet> GetBullets(); // same as player, this logic might be redundant, and may need to be made private.

    int getRandomDirection(); //a function that spits out a random number of either 1 or -1 for initial move direction for enemy ships.

protected:
    int m_health;
    int m_shields;
    int moveDir;
    float m_speed;
    int m_damage;
    std::vector<Bullet> m_bullets;
    bool m_markedForDeletion;
  
    sf::Time moveCooldown;
    sf::Time shootCooldown;
    sf::Clock moveCooldownTimer;
    sf::Clock shootCooldownTimer;

    bool firstSpawn;

private:
};