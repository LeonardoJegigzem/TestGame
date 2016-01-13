#include "player/utils/MapUtils.h"

#include "player/Status.h"

Status* MapUtils::mapStatus(std::string statusName)
{
    Status* aux;
    if(statusName == STAND_RIGHT_ID)
        aux = new StandRightStatus();
    else if(statusName == STAND_LEFT_ID)
        aux = new StandLeftStatus();
    else if(statusName == WALK_RIGHT_ID)
        aux = new WalkRightStatus();
    else if(statusName == WALK_LEFT_ID)
        aux = new WalkLeftStatus();
    else if(statusName == FALL_RIGHT_ID)
        aux = new FallRightStatus();
    else if(statusName == FALL_LEFT_ID)
		aux = new FallLeftStatus();
	else if(statusName == STAND_ATTACK_LEFT_ID)
		aux = new StandLeftAttackStatus();
	else if(statusName == STAND_ATTACK_RIGHT_ID)
		aux = new StandRightAttackStatus();
	else
        aux = new StandRightStatus();

    return aux;
}

std::string MapUtils::mapStatusAttackToMove(std::string statusName)
{
	if(statusName == STAND_ATTACK_LEFT_ID)
		return STAND_LEFT_ID;
	else if(statusName == STAND_ATTACK_RIGHT_ID)
		return STAND_RIGHT_ID;
	else
		return statusName;
}
