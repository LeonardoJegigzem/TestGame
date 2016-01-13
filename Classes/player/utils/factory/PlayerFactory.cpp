#include "player/utils/factory/PlayerFactory.h"
#include "infra/context/Context.h"
#include "player/utils/MapUtils.h"
#include "character/constants/CharacterConstants.h"

Player* PlayerFactory::createPlayer(PlayerDescriptor* descriptor)
{

	bool isLoaded = descriptor->isLoaded();
	/* Indica que un player se encuentra cargado en ese momento, por lo que NO es necesario instanciar uno nuevo
	 * en cambio, se hacen las modificaciones que indique el nuevo nivel sobre el player actualmente en memoria */
	if (isLoaded)
	{
		Player* player = Context::getInstance()->getCurrentPlayer();
		player->setCurrentStatus(MapUtils::mapStatus(descriptor->getStatus()));
		player->setPosition(descriptor->getPosition());
		return player;
	}

	std::string type = descriptor->getType();
	if (type == "non-playable-character")
		return NULL;
	else if (type == "playable-character")
		return new Character(descriptor->getStatus(),
				descriptor->getAnimation(), descriptor->getPosition(),
				descriptor->getAnimationMap(), PLAYABLE_LIFE_POINTS,
				descriptor->getInitWeapon(), descriptor->getWeaponDescriptor());
	else
		return NULL;

}
