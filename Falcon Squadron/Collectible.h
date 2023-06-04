#pragma once
#include "Physics.h"
class Collectible :
    public Physics
{
public :
    Collectible();
    virtual ~Collectible();

    virtual void Update(sf::Time _frameTime, sf::Vector2u levelSize);
    void Draw(sf::RenderTarget& target);

    virtual int Modify()= 0; // allows child classes in the vector of collectibles to have their individual modify function called.

    virtual bool IsMarkedForDeletion() const;
    virtual void SetMarkedForDeletion(bool value);
    virtual int GetPickupID() = 0;

    virtual sf::Clock GetAliveTime();

    virtual void UpdatePosition(sf::Time _frameTime, sf::Vector2u levelSize); // allows iterating through a vector of collectibles to have their position updated.

protected:
    int modValue;
    int speed;
    bool firstSpawn;
    int pickupID;

    bool markedForDeletion;
    sf::Time lifeTime;
    sf::Clock lifeCounter;
};

