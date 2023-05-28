#pragma once
#include "Physics.h"
class Bullet :
    public Physics
{
public:
    Bullet(float _speed, int _damage, bool _isPlayerFired);

    void Update(sf::Time _frameTime);
    void SetDamage(int damage);
    void SetBulletPath(sf::Time _frameTime);


private:

    float speed;
    int damage;
    bool isPlayerFired;

};

