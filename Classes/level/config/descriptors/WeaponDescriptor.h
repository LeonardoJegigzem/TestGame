#ifndef _WEAPON_DESCRIPTOR_H_
#define _WEAPON_DESCRIPTOR_H_

#include "thirdparty/rapidxml.hpp"
#include "level/config/descriptors/AnimationsDescriptor.h"

#include <string>
#include <map>

/**
 *    @class WeaponDescriptor
 *    @brief Describe el tag <weapon>
 *    @author djg
 *    @date 13/07/2015
 */
class WeaponDescriptor
{
public:
	WeaponDescriptor(rapidxml::xml_node<>* weapon);
	~WeaponDescriptor();

	std::string getCategory();

	AnimationsDescriptor* getAnimationsDescriptor();

private:
	std::string _category;
	AnimationsDescriptor* _animations;

	void loadAnimationMap(rapidxml::xml_node<>* anim);

};

#endif
