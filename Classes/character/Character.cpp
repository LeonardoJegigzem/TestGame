#include "character/Character.h"
#include "player/animation/AnimationStore.h"
#include "character/weapon/factory/WeaponFactory.h"


Character::Character(std::string status, std::string animation, Vec2 position,
		std::map<std::string, AnimationsDescriptor*> animations, int lifePoints,
		std::string currentWeaponId, WeaponDescriptor* weaponDescriptor) :
		ScrollingPlayer(status, animation, position, animations)
{

	this->_lifePoints = lifePoints;

	AnimationStore::getInstance()->addNewAnimationContainer(
			weaponDescriptor->getAnimationsDescriptor()->getId(),
			weaponDescriptor->getAnimationsDescriptor()->getAtlasPath(),
			weaponDescriptor->getAnimationsDescriptor()->getAnimationList());

	/// SIEMPRE TIENE QUE ESTAR CARGADO PREVIAMENTE LAS ANIMACIONES DEL WEAPON ANTES DE INSTANCIAR UNO!
	/// Revisar como hacer para poder hacer esto en otro lugar, no deberia hacerlo el Character :/
	this->_currentWeapon = WeaponFactory::createWeapon(currentWeaponId);
	this->_currentWeapon->setPosition(_position);


}

Character::~Character()
{
	delete this->_currentWeapon;
}

int Character::getLifePoints()
{
	return this->_lifePoints;
}

Weapon* Character::getCurrentWeapon()
{
	return this->_currentWeapon;
}

void Character::switchToWeapon(std::string weaponId)
{
	this->_currentWeapon = this->_weaponList[weaponId];
}

