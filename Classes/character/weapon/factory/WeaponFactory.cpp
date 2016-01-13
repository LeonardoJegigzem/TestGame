#include "character/weapon/factory/WeaponFactory.h"
#include "character/weapon/constants/WeaponId.h"

Weapon* WeaponFactory::createWeapon(std::string weaponId)
{
	if(weaponId == ID_COMMON_SWORD)
		return new CommonSword();
	else return NULL;
}

