#pragma once
#include "MovingStraightObject.h"

class Projectile : public MovingStraightObject
{
//---------------------------------------------------------- Methods
public:
    using MovingStraightObject::MovingStraightObject;

protected:
    virtual bool CanExitScreenSpace() const override { return false; }
    virtual double GetGravityScale() const override { return 0; }
};
