#ifndef _PLAYER_DESCRIPTOR_H_
#define _PLAYER_DESCRIPTOR_H_

#include "thirdparty/rapidxml.hpp"

#include "level/config/descriptors/AnimationDescriptor.h"
#include "level/config/descriptors/AnimationsDescriptor.h"
#include "level/config/descriptors/WeaponDescriptor.h"


#include "math/Vec2.h"
#include <string>
#include <map>
#include <vector>

/**
*    @class PlayerDescriptor
*    @brief Describe el tag <player>
*    @author djg
*    @date 11/12/2014
*/

using namespace cocos2d;

class PlayerDescriptor
{
public:
    PlayerDescriptor(rapidxml::xml_node<>* player);
    ~PlayerDescriptor();
    std::string getType();
    std::string getStatus();
    std::string getAnimation();
    Vec2 getPosition();

    std::string getInitWeapon();

	bool isLoaded();

    std::map<std::string, AnimationsDescriptor*> getAnimationMap();
    WeaponDescriptor* getWeaponDescriptor();

private:
	std::string _loaded; /* Indica si el player está cargado */
    std::string _type; /* Tipo de player a crear*/
    std::string _status; /* Estado inicial */
    std::string _animation;
    std::string _initWeapon; /* Id del arma inicial */
    Vec2 _position; /* Posicion incial del player */

    WeaponDescriptor* _weapon;
    std::map<std::string, AnimationsDescriptor*> _animations; /* Anim_ID -> Animations, Map que describe las diferentes animaciones del id asociado
                                                                Por ejemplo todos los tipos de animaciones que corresponden a la animacion de "walk"
                                                             */
    void loadAnimationMap(rapidxml::xml_node<>* anim);

};

#endif // _PLAYER_DESCRIPTOR_H_
