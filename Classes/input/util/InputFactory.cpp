#include "input/util/InputFactory.h"
#include "ConfigConst.h"

InputManager* InputFactory::getInputManager()
{
	#ifdef INPUT_VK_ENABLED
		return VirtualJoystickInputManager::getInstance();
	#elif INPUT_TOUCH_ENABLED
		return TouchScreenInputManager::getInstance();
	#endif
	
}