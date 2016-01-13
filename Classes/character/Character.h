#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "player/Player.h"
#include "character/weapon/Weapon.h"
#include "level/config/descriptors/WeaponDescriptor.h"

#include <map>
#include <string>

/// La clase Character representa al personaje sea NPC o no dentro del juego en si mismo, es decir, sus armas y habilidades as� como los puntos de vida
/// mientras que el ScrollingPlayer representa todas las acciones que se pueden realizar sobre un personaje scrolling as� como manejar los estados en el que se encuentra
class Character: public ScrollingPlayer
{

public:
	Character(std::string status, std::string animation, Vec2 position,
			std::map<std::string, AnimationsDescriptor*> animations,
			int lifePoints, std::string currentWeaponId,
			WeaponDescriptor* weaponDescriptor);
	~Character();

	int getLifePoints();
	Weapon* getCurrentWeapon() override;
	void switchToWeapon(std::string weaponId);

protected:
	int _lifePoints;
	std::map<std::string, Weapon*> _weaponList;
	Weapon* _currentWeapon;

};

class PlayableCharacter: public Character
{
public:

};

class NotPlayableCharacter: public Character
{

};

#endif // _CHARACTER_H_
