#include "player/triggers/Trigger.h"
#include "player/constants/StatusId.h"
#include "infra/context/Context.h"
#include "player/Player.h"
#include "player/utils/MapUtils.h"

void StatusTrigger::swapStatus(std::string statusName)
{
	/* Mejorar esto para que tenga un clase por cada tipo de mapeo */
	Player* player = Context::getInstance()->getCurrentPlayer();
	player->setCurrentStatus(MapUtils::mapStatus(statusName));
	player->runAnimationByCode(MapUtils::mapStatusAttackToMove(statusName));

}
