#include "character/weapon/Weapon.h"
#include "player/animation/AnimationStore.h"
#include "infra/ResPathConstants.h"

Weapon::Weapon(std::string id, unsigned int maxUpgrades, float damage, std::string category)
{
	this->_id = id;
	this->_maxUpgrades = maxUpgrades;
	this->_damage = damage;
	this->_currentUpgrade = 0;
	this->_category = category;

	this->_handler = AnimationStore::getInstance()->getAnimationContainerById(category);
	// Category y el id del animations tienen que se el mismo dentro de cada grupo!

	this->init();
	this->_handler->getNode()->addChild(this,1);
	this->runAnimationByCode("COMMON_SWORDR");
}

Weapon::~Weapon()
{

}

unsigned int Weapon::getMaxUpgrades()
{
	return this->_maxUpgrades;
}

unsigned int Weapon::getCurrentUpgrade()
{
	return this->_currentUpgrade;
}

float Weapon::getDamage()
{
	return this->_damage;
}

std::string Weapon::getCategory()
{
	return this->_category;
}

float Weapon::getDamageBonusForWeakness(std::string type)
{
	return this->_typeWeaknessXDamageMap.at(type);
}

AnimationHandler* Weapon::getAnimationHandler()
{
	return this->_handler;
}

void Weapon::runAnimationByCode(std::string weaponId)
{
	this->runAction(this->_handler->getActionByKey(weaponId));
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


