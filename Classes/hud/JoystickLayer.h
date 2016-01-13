#ifndef _HUD_LAYER_H_
#define _HUD_LAYER_H_

#include "cocos2d.h"
#include "ConfigConst.h"
#include "level/constants/SizeConstants.h"

#include "thirdparty/sneakyjoystick/SneakyButton.h"
#include "thirdparty/sneakyjoystick/SneakyJoystick.h"
#include "thirdparty/sneakyjoystick/SneakyButtonSkinnedBase.h"
#include "thirdparty/sneakyjoystick/SneakyJoystickSkinnedBase.h"



USING_NS_CC;


class JoystickLayer : public cocos2d::Layer
{
public:
    //~JoystickLayer();
    CREATE_FUNC(JoystickLayer);
    virtual bool init();
private:
	
	void generateJoystick();

    SpriteBatchNode* _node;
	SneakyJoystick* _joystick;
	SneakyButton* _jumpButton;
	SneakyButton* _attackButton;

	SneakyJoystickSkinnedBase* _base;

};


#endif
