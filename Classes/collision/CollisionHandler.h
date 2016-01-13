#ifndef _COLLISION_HANDLER_H_
#define _COLLISION_HANDLER_H_

#include "cocos2d.h"
#include "level/LevelBackground.h"
#include "collision/CollisionInfo.h"
#include "player/constants/StatusId.h"

USING_NS_CC;

class CollisionHandler
{
public:
    static CollisionInfo getCollisionInfo(std::string currentStatusDescription, Vec2 position);
    static void setMetaLayer(TMXLayer* metaLayer);
    static void setLevelBackground(LevelBackground* background);
private:
    static LevelBackground* _levelback;/// Estos valores hay que setearlos para poder obtener las colisiones!!!!!!
    static TMXLayer* _layer;///
	
	static void checkBounds(Vec2 position, CollisionInfo &info);
	static void checkBackgroundCollision(Vec2 position, std::string currentStatusDescription, CollisionInfo &info);
};


#endif // _COLLISION_HANDLER_H_
