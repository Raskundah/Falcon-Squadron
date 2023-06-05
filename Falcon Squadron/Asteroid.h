#pragma once
#include "SpriteObject.h"
#include "Physics.h"
class Asteroid :
    public Physics
{
public:
    Asteroid();

    void Update(sf::Time frameTime, sf::Vector2u levelSize);
    void Draw(sf::RenderTarget& target);
    bool IsMarkedForDeletion() const; // checks if an instance is marked for deletion
    void SetMarkedForDeletion(bool value); // sets marked for deletion.
    sf::Clock GetAsteroidAliveTime(); // counts each asteroids time in existence, needed for respawning off screen asteroids. 

    void HandleCollision(Physics& other); // right now we don't handle collision in here
    //the plan is to add an ID field to all physics objects and use that to handle collision internally. If you're reading this sarah, I'm sorry that level screen does too much and may break OOP. :P

    bool GetDamageCheck();
    void SetDamageCheck(bool toSet);

    void SetPosition(sf::Time frameTime, sf::Vector2u levelSize); 
    int GetDamage(); // gets the asteroid's damage. 
    int GetHealth();
    int GetScore();
    void TakeDamage(); // simple function that reduces the amount of hits the astroid can still take. This is 1, regardless of input and health is set at 4.
    // this is similar to tiamat's wave minions in smite. it also uses a this pointer to locally identify which asteroid is to be deleted, avoiding looping through the asteroids
    // marked for deletion. It may be possible to do this for enemies, negating the need for the fancy clean up function(s).

private:
    int speed, damageToPlayer, score;
    bool firstSpawn;
    bool markedForDeletion;
    bool hasDamagedPlayerRecently;
    int damageCounter;

    sf::Time lifeTime, checkCollisionTimer;
    sf::Clock deleteTimer, collisionTimer;

};
