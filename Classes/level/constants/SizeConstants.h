#ifndef _SIZE_CONSTANTS_H_
#define _SIZE_CONSTANTS_H_

#include <base/CCDirector.h>

#define SCREEN_W Director::getInstance()->getVisibleSize().width
#define SCREEN_H Director::getInstance()->getVisibleSize().height

#define UIPointToGLPoint(point) Director::getInstance()->convertToGL(point)




#endif // _SIZE_CONSTANTS_H_
