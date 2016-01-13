#ifndef _PLAYER_FACTORY_H_
#define _PLAYER_FACTORY_H_

#include <string>
#include "level/config/descriptors/PlayerDescriptor.h"

#include "player/Player.h"
#include "character/Character.h"

class PlayerFactory
{
public:
	static Player* createPlayer(PlayerDescriptor* descriptor);
};

#endif
