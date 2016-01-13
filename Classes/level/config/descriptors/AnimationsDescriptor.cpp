#include "level/config/descriptors/AnimationsDescriptor.h"

#include "level/util/LevelConfigMacros.h"

AnimationsDescriptor::AnimationsDescriptor(rapidxml::xml_node<>* animations)
{
	this->_id = NotNull(animations->first_attribute("id"));
	//Contiene el path del atlas en el que están definidos los sprites de las animaciones que se encuentren como hijos del tag <animations>
	this->_atlasPath = Optional(animations->first_attribute("atlasName"));

	for (rapidxml::xml_node<>* animation = animations->first_node("animation"); animation != NULL; animation = animation->next_sibling())
	{
		this->_animations.push_back(new AnimationDescriptor(animation));
	}

}

AnimationsDescriptor::~AnimationsDescriptor()
{
    for(auto &anim: this->_animations)
    {
       delete anim;
    }
}

std::vector<AnimationDescriptor*> AnimationsDescriptor::getAnimationList()
{
	return this->_animations;
}

std::string AnimationsDescriptor::getId()
{
	return this->_id;
}


std::string AnimationsDescriptor::getAtlasPath()
{
	return this->_atlasPath;
}
