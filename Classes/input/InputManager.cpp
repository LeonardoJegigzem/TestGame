#include "input/InputManager.h"
#include "level/constants/SizeConstants.h"
#include "player/constants/MovConstants.h"
#include "input/constants/InputConstants.h"

InputManager* InputManager::_instance = NULL;


void InputManager::resetInstance()
{
	delete _instance;
	_instance = NULL;
}

///Cada nodo va a tener asignado un evento al cual funciona como source para decidir la accion a tomar
///dicho valor se mapea evento->nodo y de allí se obtiene un valor que luego es casteado correspondientemente
void InputManager::setEventSource(InputNode* node, int event)
{
    if(event == EVENT::ALL)
    {
        for(int cevent = EVENT::LEFT; cevent != EVENT::ALL; cevent++)
        {
            this->_eventAttachedToNode[cevent] = node;
        }
    }
    else
    {
        this->_eventAttachedToNode[event] = node;
    }

}

template <typename T>
T InputManager::getDataAs(int event) /// Retorna un casteo del data del InputNode al tipo T para el evento indicado
{
	T* ret = static_cast<T*>(_eventAttachedToNode[event]->getData());
	return *ret;
}


///*********************************************************************************************************************************************

InputManager* TouchScreenInputManager::getInstance()
{
     if(_instance == NULL)
    {
        _instance = new TouchScreenInputManager();
        _instance->initializeEvents();
    }

    return _instance;
}

void TouchScreenInputManager::initializeEvents()
{
    _orientation = ORIENTATION_NONE;
    _touchCounter = 0;

    _sideListener = EventListenerTouchOneByOne::create();
    _sideListener->onTouchBegan = [&](Touch* touch, Event* event)
    {

        auto position = touch->getLocationInView();
        _orientation = position.x > SCREEN_W/2;

        return true;
    };
    _sideListener->onTouchEnded = [&](Touch* touch, Event* event)
    {
          _orientation = ORIENTATION_NONE;
    };


    _countListener = EventListenerTouchOneByOne::create();
    _countListener->onTouchBegan = [&](Touch* touch, Event* event)
    {
        _touchCounter++;
        return true;
    };
    _countListener->onTouchEnded = [&](Touch* touch, Event* event)
    {
        _touchCounter--;

    };
}

void TouchScreenInputManager::setEventSource(InputNode* node, int event)
{
    node->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_sideListener, node);
    node->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_countListener, node);
}

bool TouchScreenInputManager::isLeftEvent()
{
    return _orientation == ORIENTATION_LEFT;
}

bool TouchScreenInputManager::isRightEvent()
{
    return _orientation == ORIENTATION_RIGHT;
}

bool TouchScreenInputManager::isStandEvent()
{
    return _orientation == ORIENTATION_NONE;
}

bool TouchScreenInputManager::isUpEvent()
{
    return false;
}

bool TouchScreenInputManager::isDownEvent()
{
    return false;
}


bool TouchScreenInputManager::isJumpEvent()
{
    return this->_touchCounter == 2;
}

int TouchScreenInputManager::getTouchCount()
{
    return this->_touchCounter;
}

/**************************************************************************************************************************************/



InputManager* VirtualJoystickInputManager::getInstance()
{
     if(_instance == NULL)
    {
        _instance = new VirtualJoystickInputManager();
        _instance->initializeEvents();
    }

    return _instance;
}

void VirtualJoystickInputManager::initializeEvents()
{

}

bool VirtualJoystickInputManager::isLeftEvent()
{
	Point pos = getDataAs<Point>(EVENT::LEFT);

	return pos.x < -DEADZONE;
}

bool VirtualJoystickInputManager::isRightEvent()
{
	Point pos = getDataAs<Point>(EVENT::RIGHT);
	return pos.x > DEADZONE ;
}

bool VirtualJoystickInputManager::isStandEvent()
{
	Point pos = getDataAs<Point>(EVENT::STAND);
	return OnInterval(pos.x, DEADZONE); /// Si la posicion se encuentra dentro de la Deadzone, se tiene que anular el movimiento
}

bool VirtualJoystickInputManager::isUpEvent()
{
    return false;
}

bool VirtualJoystickInputManager::isDownEvent()
{
    return false;
}


bool VirtualJoystickInputManager::isJumpEvent()
{
	bool pressed = getDataAs<bool>(EVENT::JUMP);
    return pressed;
}

bool VirtualJoystickInputManager::isAttackEvent()
{
	bool pressed = getDataAs<bool>(EVENT::ATTACK);
	return pressed;
}
