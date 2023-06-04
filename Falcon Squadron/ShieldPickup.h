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

    void Modify(int varInt);

    bool IsMarkedForDeletion() const;
    void SetMarkedForDeletion(bool value);

    sf::Clock GetAliveTime();


    void UpdatePosition(sf::Time _frameTime, sf::Vector2u levelSize);


};