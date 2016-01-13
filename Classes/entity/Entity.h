#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "cocos2d.h"
#include "collision/CollisionInfo.h"
#include "player/constants/MovConstants.h"


USING_NS_CC;

class Entity : public Sprite
{
public:
    virtual void update()=0; ///Metodo llamado por el update de las escenas para cada Entity
};

class EntityWithMass : public Entity
{
public:
    EntityWithMass();

    virtual void collision() = 0;

    bool isCollisionable();
    bool hasGravity();
    void setCollisionable(bool collionable);
    void setGravityFlag(bool gravityFlag);

    void setPosition(const Vec2& position);

private:
    bool _collisionable;
    bool _applyGravity;
};


#endif // _ENTITY_H_
