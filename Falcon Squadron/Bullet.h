#pragma once
#include "Physics.h"
class Bullet :
    public Physics
{
public:
    void Update(sf::Time _frameTime);
    bool IsMarkedForDeletion() const;
    void SetMarkedForDeletion(bool value);
    void SetDamage(int _damage);

    Bullet(float _speed, int _damage, bool _isPlayerFired, sf::Time _lifetime);

    void SetBulletPath(sf::Time _frameTime);
    void SetSpriteTexture(sf::Texture i_bullet);

private:

    float speed;
    int damage;
    bool isPlayerFired;
    bool markedForDeletion;

    sf::Time lifetime; // the predefined lifespan of any bullet.
    sf::Clock lifetimeTimer; //counts down from the max timer.

};

