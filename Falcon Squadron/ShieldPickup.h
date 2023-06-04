#pragma once
#include <SFML/Graphics.hpp>
#include "Collectible.h"

class ShieldPickup :
    public Collectible
{
 
public:
    ShieldPickup();
    ~ShieldPickup();

    void Update(sf::Time _frameTime, sf::Vector2u levelSize);
    void Draw(sf::RenderTarget& target);

    int Modify();

    bool IsMarkedForDeletion() const;
    void SetMarkedForDeletion(bool value);

    sf::Clock GetAliveTime();

    int GetPickupID();


    void UpdatePosition(sf::Time _frameTime, sf::Vector2u levelSize);


};