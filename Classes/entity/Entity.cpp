#include "entity/Entity.h"


EntityWithMass::EntityWithMass()
{
    this->_applyGravity = true;
    this->_collisionable = true;
}

bool EntityWithMass::isCollisionable()
{
    return this->_collisionable;
}

bool EntityWithMass::hasGravity()
{
    return this->_applyGravity;
}

void EntityWithMass::setPosition(const Vec2& position)
{
    if(this->hasGravity())
        Sprite::setPosition(position + GRAVITY);
    else
        Sprite::setPosition(position);
}


void EntityWithMass::setCollisionable(bool collisionable)
{
    this->_collisionable = collisionable;
}

void EntityWithMass::setGravityFlag(bool gravityFlag)
{
    this->_applyGravity = gravityFlag;
}
