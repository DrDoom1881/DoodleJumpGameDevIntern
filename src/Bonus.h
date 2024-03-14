#pragma once
#include "Object.h"
#include "mFramework.h"
class Bonus : public MoveableObject
{

public:
    Bonus(float x, float y, float width, float height) : MoveableObject(x, y, width, height)
    {
        deltaY = 0.55;
    }
    ~Bonus();

    virtual void move() override;

};
