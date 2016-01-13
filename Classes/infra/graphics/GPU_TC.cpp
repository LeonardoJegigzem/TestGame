#include "infra/graphics/GPU_TC.h"
#include "infra/graphics/TC_EXT_DEF.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

std::string getTC()
{
    if(cocos2d::Configuration::getInstance()->supportsPVRTC())
        return PVR_EXT;
    else if(cocos2d::Configuration::getInstance()->supportsATITC())
        return ATI_EXT;
    else
        return DEFAULT_EXT;

}

#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#endif

