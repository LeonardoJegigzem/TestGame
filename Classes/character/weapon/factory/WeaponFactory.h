#ifndef _WEAPON_FACTORY_H_
#define _WEAPON_FACTORY_H_

#include "character/weapon/Weapon.h"

class WeaponFactory
{
public:
	static Weapon* createWeapon(std::string weaponId);
};

#endif
