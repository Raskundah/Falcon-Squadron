#pragma once
#include "SpriteObject.h"
#include "Physics.h"

class Physics;

class Player :
    public SpriteObject
{
    public:
        Player();

        void Update();


};

