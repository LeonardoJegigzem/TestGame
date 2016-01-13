#ifndef _ANIMATIONS_DESCRIPTOR_H_
#define _ANIMATIONS_DESCRIPTOR_H_

#include "thirdparty/rapidxml.hpp"

#include "level/config/descriptors/AnimationDescriptor.h"

#include <vector>
#include <string>

/**
*    @class AnimationsDescriptor
*    @brief Describe el tag <animations>
*    @author djg
*    @date 13/07/2015
*/
class AnimationsDescriptor
{
public:
	AnimationsDescriptor(rapidxml::xml_node<>* animations);
	~AnimationsDescriptor();
	std::vector<AnimationDescriptor*> getAnimationList();
	std::string getId();
	std::string getAtlasPath();

private:
	std::string _id;
	std::string _atlasPath;
	std::vector<AnimationDescriptor*> _animations;

};

#endif
