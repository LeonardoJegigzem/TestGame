#include "level/config/descriptors/WeaponDescriptor.h"
#include "level/util/LevelConfigMacros.h"

WeaponDescriptor::WeaponDescriptor(rapidxml::xml_node<>* weapon)
{
	this->_category = NotNull(weapon->first_attribute("category"));

	rapidxml::xml_node<>* animations = NotNullTag(weapon->first_node("animations"));

	_animations = new AnimationsDescriptor(animations);

}

WeaponDescriptor::~WeaponDescriptor()
{

	delete this->_animations;

}

std::string WeaponDescriptor::getCategory()
{
	return this->_category;
}

AnimationsDescriptor* WeaponDescriptor::getAnimationsDescriptor()
{
	return this->_animations;
}
