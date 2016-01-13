#ifndef _ANIMATED_INTERFACE_H_
#define _ANIMATED_INTERFACE_H_

#include "player/AnimationHandler.h"
#include <string>

class AnimatedInterface
{
public:
	virtual ~AnimatedInterface(){};

	virtual AnimationHandler* getAnimationHandler() = 0;
	virtual void runAnimationByCode(std::string key) = 0;
};


#endif
