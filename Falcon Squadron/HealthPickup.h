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

    void Modify(int varInt);

    bool IsMarkedForDeletion() const;
    void SetMarkedForDeletion(bool value);

    void UpdatePosition(sf::Time _frameTime, sf::Vector2u levelSize);


};

