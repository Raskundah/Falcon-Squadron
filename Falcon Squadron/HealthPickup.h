#pragma once
#include <SFML/Graphics.hpp>
#include "Collectible.h"

class HealthPickup :
    public Collectible
{
public:
    HealthPickup();
    ~HealthPickup();

    void Update(sf::Time _frameTime, sf::Vector2u levelSize);
    void Draw(sf::RenderTarget& target);

    int Modify(); //returns the pickups modify attribute value

    bool IsMarkedForDeletion() const;
    void SetMarkedForDeletion(bool value);

    int GetPickupID();


    void UpdatePosition(sf::Time _frameTime, sf::Vector2u levelSize);


};

