#include "level/config/descriptors/PlayerDescriptor.h"
#include "level/constants/SizeConstants.h"
#include "level/util/LevelConfigMacros.h"

PlayerDescriptor::PlayerDescriptor(rapidxml::xml_node<>* player)
{

	/* Cargo primero la posición porque es un valor que siempre puedo tomar aunque esté como loaded */
	rapidxml::xml_node<>* pos = NotNullTag(player->first_node("position"));

	std::string x = NotNull(pos->first_attribute("x"));
	std::string y = NotNull(pos->first_attribute("y"));

	this->_position.x = x == "CENTER" ? SCREEN_W/2 : std::stof(x);
	this->_position.y = y == "CENTER" ? SCREEN_H/2 : std::stof(y);

	this->_status = NotNull(player->first_attribute("status"));
	this->_weapon = NULL;

	/* Los campos necesarios cuando es loaded tiene que estar definidos antes del OptionalReturn! */
	this->_loaded = OptionalReturn(player->first_attribute("loaded"));

	this->_type = NotNull(player->first_attribute("type"));
	this->_animation = NotNull(player->first_attribute("use-animation"));


	/* Itero sobre cada ID de animación */
	rapidxml::xml_node<>* anim = NotNullTag(player->first_node("animations"));
	loadAnimationMap(anim);

	rapidxml::xml_node<>* weapon = OptionalTag(player->first_node("weapon"));

	if(weapon != NULL)
		_weapon = new WeaponDescriptor(weapon);

	this->_initWeapon = Optional(player->first_attribute("use-weapon"));

}

PlayerDescriptor::~PlayerDescriptor()
{
	for (auto &animPair : this->_animations)
	{
		delete animPair.second;
	}

	if(_weapon != NULL)
		delete this->_weapon;
}

bool PlayerDescriptor::isLoaded()
{
	return this->_loaded == "true";
}

std::string PlayerDescriptor::getType()
{

	return this->_type;
}

std::string PlayerDescriptor::getStatus()
{
	return this->_status;
}

std::string PlayerDescriptor::getAnimation()
{
	return this->_animation;
}

Vec2 PlayerDescriptor::getPosition()
{
	return this->_position;
}

std::string PlayerDescriptor::getInitWeapon()
{
	return this->_initWeapon;
}

std::map<std::string, AnimationsDescriptor*> PlayerDescriptor::getAnimationMap()
{
	return this->_animations;
}

WeaponDescriptor* PlayerDescriptor::getWeaponDescriptor()
{
	return this->_weapon;
}

void PlayerDescriptor::loadAnimationMap(rapidxml::xml_node<>* anim)
{
	for (rapidxml::xml_node<>* animations = anim; animations != NULL; animations = animations->next_sibling())
	{

		AnimationsDescriptor* auxDesc = new AnimationsDescriptor(anim);
		std::string animationId = auxDesc->getId();

		this->_animations[animationId] = auxDesc;

	}
}

