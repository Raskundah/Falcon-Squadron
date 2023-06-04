#pragma once
#include "Physics.h"
class Collectible :
    public Physics
{
public :
    Collectible();
    virtual ~Collectible();

    void Update(sf::Time _frameTime, sf::Vector2u levelSize);
    void Draw(sf::RenderTarget& target);

    virtual void Modify(int varInt)= 0; // allows child classes in the vector of collectibles to have their individual modify function called.

    virtual bool IsMarkedForDeletion() const;
    virtual void SetMarkedForDeletion(bool value);

    virtual sf::Clock GetAliveTime();

    virtual void UpdatePosition(sf::Time _frameTime, sf::Vector2u levelSize); // allows iterating through a vector of collectibles to have their position updated.

protected:
    int modValue;
    int speed;
    bool firstSpawn;
    bool markedForDeletion;
    sf::Time lifeTime;
    sf::Clock lifeCounter;
};

