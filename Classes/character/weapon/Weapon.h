#ifndef _WEAPON_H_
#define _WEAPON_H_

#include "cocos2d.h"

#include "player/AnimationHandler.h"
#include "player/animation/AnimatedInterface.h"

#include "level/config/descriptors/AnimationsDescriptor.h"
#include "character/weapon/constants/WeaponCategory.h"
#include "character/weapon/constants/WeaponId.h"
#include "character/weapon/constants/WeaponStatsConstants.h"



USING_NS_CC;

// Segun un post en SO, lo mejor para correr dos animaciones a la vez es crear un sprite nuevo con las animaciones que se quieran....

class Weapon: public Sprite, public AnimatedInterface
{

protected:
	Weapon(std::string id, unsigned int maxUpgrades, float damage, std::string category);

public:
	~Weapon();
	std::string getId();
	unsigned int getMaxUpgrades();
	unsigned int getCurrentUpgrade();
	float getDamage();
	float getDamageBonusForWeakness(std::string type);

	std::string getCategory();

	AnimationHandler* getAnimationHandler() override;
	void runAnimationByCode(std::string key) override;

private:
	std::string _id;
	unsigned int _maxUpgrades;
	unsigned int _currentUpgrade;
	float _damage;
	std::string _category;
	std::map<std::string, float> _typeWeaknessXDamageMap;

	AnimationHandler* _handler;


};

////////////////////////////////////////////////////////////////////////////////////////////////////////
class Sword: public Weapon
{
public:
	Sword(std::string id, unsigned int maxUpgrades, float damage) : Weapon(id, maxUpgrades, damage, CATEGORY_SWORD){};

};

////////////////////////////////////////////////////////////////////////////////////////////////////////
class CommonSword: public Sword
{
public:
	CommonSword() : Sword(ID_COMMON_SWORD, UPGRADE_COMMON_SWORD_MAX, DAMAGE_COMMON_SWORD){};
};

#endif // _WEAPON_H_
