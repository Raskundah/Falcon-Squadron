#pragma once
#include "Physics.h"
class Bullet :
    public Physics
{
public:
    void Update(sf::Time _frameTime);
    void Draw(sf::RenderTarget& _target);
    bool IsMarkedForDeletion() const;
    void SetMarkedForDeletion(bool value); // much like other classes, these functions internall handle deletion.
    void SetDamage(int _damage); // sets the bullet's damage, don't think this is currently used.

    Bullet(float _speed, int _damage, bool _isPlayerFired, sf::Time _lifetime); // the glorious bullet constructor.

    void SetBulletPath(sf::Time _frameTime);
    void SetSpriteTexture(sf::Texture i_bullet); // unused currently, this is intended to give players and different ship a different bullet texture.  May cause collision errors potentially.
    bool GetShooter(); // returns who shot the bullet. 

private:

    float speed;
    int damage;
    bool isPlayerFired;
    bool markedForDeletion;  

    sf::Time lifetime; // the predefined lifespan of any bullet.
    sf::Clock lifetimeTimer; //counts down from the max timer.

};

