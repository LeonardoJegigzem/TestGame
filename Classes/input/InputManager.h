#ifndef _INPUT_MANAGER_H_
#define _INPUT_MANAGER_H_

#include "cocos2d.h"

#include "thirdparty/sneakyjoystick/SneakyJoystick.h"
#include "thirdparty/sneakyjoystick/SneakyButton.h"
#include "input/InputNode.h"

USING_NS_CC;

/* InputManager proporciona una interfaz para abstraer cada uno de los posible m�todos de entrada ya sea :

    * Touch
	* VirtualJoystick
    * Keyboard
    * Joystick

*/

class InputManager
{
public:

	static void resetInstance();

	virtual ~InputManager(){};
    virtual void initializeEvents() = 0;
    virtual void setEventSource(InputNode* node, int event = EVENT::ALL);
    virtual bool isLeftEvent() = 0;
    virtual bool isRightEvent() = 0;
    virtual bool isStandEvent() = 0;
    virtual bool isUpEvent() = 0;
    virtual bool isDownEvent() = 0;
    virtual bool isJumpEvent() = 0;
    virtual bool isAttackEvent() = 0;
	


	enum EVENT{LEFT = 0, RIGHT, UP, DOWN, JUMP, STAND, ATTACK, ALL};
	
protected:

	template<typename T>
	T getDataAs(int event);

    static InputManager* _instance;
	std::map<int, InputNode*> _eventAttachedToNode;

};


/// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class TouchScreenInputManager : public InputManager
{

public:

    static InputManager* getInstance();

    void initializeEvents() override;
    void setEventSource(InputNode* node, int event) override;

    bool isLeftEvent() override;
    bool isRightEvent() override;
    bool isStandEvent() override;
    bool isUpEvent() override;
    bool isDownEvent() override;
    bool isJumpEvent() override;
    bool isAttackEvent() {return false;};


    int getTouchCount();

private:



    int _orientation; ///Esta variable es modificada por los listeners!
    int _touchCounter;

    EventListenerTouchOneByOne* _sideListener;
//    EventListener* _jumpListener;
    EventListenerTouchOneByOne* _countListener;


};


class VirtualJoystickInputManager : public InputManager
{
	
public:
	static InputManager* getInstance();

    void initializeEvents() override;

    bool isLeftEvent() override;
    bool isRightEvent() override;
    bool isStandEvent() override;
    bool isUpEvent() override;
    bool isDownEvent() override;
    bool isJumpEvent() override;
    bool isAttackEvent() override;

};


#endif // _INPUT_MANAGER_H_
