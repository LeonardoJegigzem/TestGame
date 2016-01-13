#include "level/config/descriptors/AnimationDescriptor.h"
#include "level/util/LevelConfigMacros.h"

AnimationDescriptor::AnimationDescriptor(rapidxml::xml_node<>* animation)
{
    this->_status = NotNull(animation->first_attribute("status"));
    this->_pattern = NotNull(animation->first_attribute("pattern"));
	
	std::string frames = NotNull(animation->first_attribute("frames"));
    this->_frames = std::stoi(frames);

    std::string speed =  Optional(animation->first_attribute("speed"));
    speed = MapNullToZero(speed);

    this->_animationSpeed = std::stof(speed);

    this->_animationType = Optional(animation->first_attribute("type"));
}

std::string AnimationDescriptor::getStatus()
{
    return this->_status;
}

std::string AnimationDescriptor::getPattern()
{
    return this->_pattern;
}

int AnimationDescriptor::getFrameCount()
{
    return this->_frames;
}

float AnimationDescriptor::getAnimationSpeed()
{
    return this->_animationSpeed;
}

std::string AnimationDescriptor::getAnimationType()
{
	return this->_animationType;
}
