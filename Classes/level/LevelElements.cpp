#include "level/LevelElements.h"

#include "player/utils/factory/PlayerFactory.h"

LevelElements::LevelElements(ElementsDescriptor* elements)
{
	generatePlayer(elements->getPlayerInfo());
}

LevelElements::~LevelElements()
{
	delete this->_player;
}

Player* LevelElements::getPlayer()
{
    return this->_player;
}

void LevelElements::generatePlayer(PlayerDescriptor* player)
{
	this->_player = PlayerFactory::createPlayer(player);

}
