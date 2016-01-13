#include "hud/JoystickLayer.h"
#include "input/InputManager.h"
#include "level/constants/SizeConstants.h"

bool JoystickLayer::init()
{
	 if (!Layer::init())
        return false;

	CCLOG("Initializing JoystickLayer...");

    this->_node = SpriteBatchNode::create("texture/joystick/joystick.png");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("texture/joystick/joystick.png.plist");

	generateJoystick();

#ifdef INPUT_VK_DYNAMIC_THUMB
	auto joystickPosListener = EventListenerTouchOneByOne::create();
	joystickPosListener->onTouchBegan = [&](Touch* touch, Event* event)
	{
		auto position = touch->getLocationInView();
		if(position.x < SCREEN_W/2)
			_base->setPosition(UIPointToGLPoint(position));
		return true;
	};
	/*
	joystickPosListener->onTouchMoved = [&](Touch* touch, Event* event)
	{
		
	};
	
	joystickPosListener->onTouchEnded = [&](Touch* touch, Event* event)
	{
		
	};
	*/
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(joystickPosListener, this);
#endif

	VirtualJoystickInputManager::getInstance()->setEventSource(_joystick, InputManager::EVENT::LEFT);
	VirtualJoystickInputManager::getInstance()->setEventSource(_joystick, InputManager::EVENT::RIGHT);
	VirtualJoystickInputManager::getInstance()->setEventSource(_joystick, InputManager::EVENT::STAND);
	VirtualJoystickInputManager::getInstance()->setEventSource(_jumpButton, InputManager::EVENT::JUMP);
	VirtualJoystickInputManager::getInstance()->setEventSource(_attackButton, InputManager::EVENT::ATTACK);

	return true;
}

void JoystickLayer::generateJoystick()
{

	Rect joystickBaseDimensions(0, 0, 6.0f, 6.0f);
	Point joystickBasePosition(SCREEN_W * 0.21f, SCREEN_H * 0.2f);

    Sprite* bg = Sprite::createWithSpriteFrameName("background.png");
    Sprite* thumb = Sprite::createWithSpriteFrameName("thumb.png");
    bg->setScale(0.37f);
    thumb->setScale(0.45f);

	SneakyJoystickSkinnedBase* joystickBase = new SneakyJoystickSkinnedBase();
	_base = joystickBase;
	joystickBase->init();
	joystickBase->setPosition(joystickBasePosition);
	joystickBase->setBackgroundSprite(bg);
	joystickBase->setThumbSprite(thumb);

	_joystick = new SneakyJoystick();
	_joystick->initWithRect(joystickBaseDimensions);
	_joystick->autorelease();
	joystickBase->setJoystick(_joystick);
	joystickBase->setPosition(joystickBasePosition);

	Rect jumpButtonDimensions(0, 0, 64.0f, 64.0f);
	Point jumpButtonPosition;
	jumpButtonPosition = ccp(SCREEN_W * 0.8f, SCREEN_H * 0.2f);

	SneakyButtonSkinnedBase *jumpButtonBase = new SneakyButtonSkinnedBase();
	jumpButtonBase->init();
	jumpButtonBase->setPosition(jumpButtonPosition);


	Sprite* button1 = Sprite::createWithSpriteFrameName("jumpButton.png");
	button1->setScale(0.6f);
	jumpButtonBase->setDefaultSprite(button1);
	jumpButtonBase->setActivatedSprite(button1);
	jumpButtonBase->setDisabledSprite(button1);
	jumpButtonBase->setPressSprite(button1);

	_jumpButton = new SneakyButton();
	_jumpButton->initWithRect(jumpButtonDimensions);
	_jumpButton->autorelease();

	jumpButtonBase->setButton(_jumpButton);
	jumpButtonBase->setPosition(jumpButtonPosition);

	_jumpButton->retain();


	Rect attackButtonDimensions(0, 0, 64.0f, 64.0f);
	Point attackButtonPosition;
	attackButtonPosition = ccp(SCREEN_W * 0.93f, SCREEN_H * 0.3f);

	SneakyButtonSkinnedBase *attackButtonBase = new SneakyButtonSkinnedBase();
	attackButtonBase->init();
	attackButtonBase->setPosition(attackButtonPosition);

	Sprite* button2 = Sprite::createWithSpriteFrameName("attackButton.png");
	button2->setScale(0.6f);
	attackButtonBase->setDefaultSprite(button2);
	attackButtonBase->setActivatedSprite(button2);
	attackButtonBase->setDisabledSprite(button2);
	attackButtonBase->setPressSprite(button2);

	_attackButton = new SneakyButton();
	_attackButton->initWithRect(attackButtonDimensions);
	_attackButton->autorelease();

	attackButtonBase->setButton(_attackButton);
	attackButtonBase->setPosition(attackButtonPosition);

	_attackButton->retain();


	this->addChild(attackButtonBase);
	this->addChild(jumpButtonBase);
	this->addChild(joystickBase);

	scheduleUpdate();
	this->setTouchEnabled(true);

}
