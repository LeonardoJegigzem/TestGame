#ifndef _ANIMATION_DESCRIPTOR_H_
#define _ANIMATION_DESCRIPTOR_H_

#include "thirdparty/rapidxml.hpp"

#include <string>
/**
*    @class AnimationDescriptor
*    @brief Describe el tag <animation>
*    @author djg
*    @date 11/12/2014
*/
class AnimationDescriptor
{
public:
    AnimationDescriptor(rapidxml::xml_node<>* animation);

    std::string getStatus();
    std::string getPattern();
    int getFrameCount();
    float getAnimationSpeed();
    std::string getAnimationType();
private:
    std::string _status;
    std::string _pattern;
    unsigned int _frames;
    float _animationSpeed;
    std::string _animationType;

};

#endif // _ANIMATION_DESCRIPTOR_H_
