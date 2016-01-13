#include "player/Status.h"
#include "player/Player.h"
#include "util/common/UtilMacros.h"
#include "player/constants/MovConstants.h"
/// Status


Status::Status(std::string status)
{
    this->_statusDescription = status;

    CCLOG("status-->%s", _statusDescription.c_str());
}

void Status::setStatusDescription(std::string status)
{
    this->_statusDescription = status;
}

std::string Status::getStatusDescription()
{
    return this->_statusDescription;
}

void Status::onWalk(int orientation, Player* player)
{
    switch(orientation)
    {
        case ORIENTATION_LEFT:
            this->onLeftWalk(player);
            break;

        case ORIENTATION_RIGHT:
            this->onRightWalk(player);
            break;

    }
}


///
/// Hace falta tener un Stand para cada sentido?, porque hacen lo mismo en los dos casos, solo cambia la imagen a mostrar
/// StandLeftStatus

void StandLeftStatus::onLeftWalk(Player* player)
{
    player->setStep(WLS_STEP);
    player->setCurrentStatus(new WalkLeftStatus());
    player->runAnimationByCode(WALK_LEFT_ID);

}

void StandLeftStatus::onRightWalk(Player* player)
{
    player->setStep(WRS_STEP);
    player->setCurrentStatus(new WalkRightStatus());
    player->runAnimationByCode(WALK_RIGHT_ID);

}

void StandLeftStatus::onJump(Player* player)
{
    player->setJumpStep(JMPS_STEP);
    player->setCurrentStatus(new JumpLeftStatus());
    player->runAnimationByCode(JUMP_LEFT_ID);

}

void StandLeftStatus::onAttack(Player* player)
{
	player->setCurrentStatus(new StandLeftAttackStatus());
	player->runAnimationByCode(STAND_ATTACK_LEFT_ID);
}

void StandLeftStatus::onCollision(Player* player, CollisionInfo collisionInfo)
{
	if(collisionInfo.isUpCollision())
	{
		player->setGravityFlag(false);
	}
}
///

/// StandRightStatus

void StandRightStatus::onLeftWalk(Player* player)
{
    player->setStep(WLS_STEP);
    player->setCurrentStatus(new WalkLeftStatus());
    player->runAnimationByCode(WALK_LEFT_ID);


}

void StandRightStatus::onRightWalk(Player* player)
{
    player->setStep(WRS_STEP);
    player->setCurrentStatus(new WalkRightStatus());
    player->runAnimationByCode(WALK_RIGHT_ID);


}

void StandRightStatus::onJump(Player* player)
{
    player->setJumpStep(JMPS_STEP);
    player->setCurrentStatus(new JumpRightStatus());
    player->runAnimationByCode(JUMP_RIGHT_ID);

}

void StandRightStatus::onAttack(Player* player)
{
	player->setCurrentStatus(new StandRightAttackStatus());
	player->runAnimationByCode(STAND_ATTACK_RIGHT_ID);
}

void StandRightStatus::onCollision(Player* player, CollisionInfo collisionInfo)
{
	if(collisionInfo.isUpCollision())
	{
		player->setGravityFlag(false);
	}
}
///

/// WalkLeftStatus

void WalkLeftStatus::onStand(Player* player)
{
    player->setStep(STAND_STEP);
    player->setCurrentStatus(new StandLeftStatus());
    player->runAnimationByCode(STAND_LEFT_ID);


}

void WalkLeftStatus::onRightWalk(Player* player)
{
    player->setStep(WRS_STEP);
    player->setCurrentStatus(new WalkRightStatus());
    player->runAnimationByCode(WALK_RIGHT_ID);

}

void WalkLeftStatus::onJump(Player* player)
{
    player->setJumpStep(JMPS_STEP);
    player->setCurrentStatus(new JumpLeftStatus());
    player->runAnimationByCode(JUMP_LEFT_ID);

}

void WalkLeftStatus::onFall(Player* player)
{
    player->setCurrentStatus(new FallLeftStatus());
    player->runAnimationByCode(FALL_LEFT_ID);

}

void WalkLeftStatus::onCollision(Player* player, CollisionInfo collisionInfo)
{
	if(collisionInfo.isRightCollision())
	{
		player->setStep(STAND_STEP);
	}
	if(collisionInfo.isUpCollision())
	{
		player->setGravityFlag(false);
	}		
}

///

/// WalkRightStatus

void WalkRightStatus::onStand(Player* player)
{
    player->setStep(STAND_STEP);
    player->setCurrentStatus(new StandRightStatus());
    player->runAnimationByCode(STAND_RIGHT_ID);

}

void WalkRightStatus::onLeftWalk(Player* player)
{
    player->setStep(WLS_STEP);
    player->setCurrentStatus(new WalkLeftStatus());
    player->runAnimationByCode(WALK_LEFT_ID);

}

void WalkRightStatus::onJump(Player* player)
{
    player->setJumpStep(JMPS_STEP);
    player->setCurrentStatus(new JumpRightStatus());
    player->runAnimationByCode(JUMP_RIGHT_ID);
}

void WalkRightStatus::onFall(Player* player)
{
    player->setCurrentStatus(new FallRightStatus());
    player->runAnimationByCode(FALL_RIGHT_ID);

}

void WalkRightStatus::onCollision(Player* player, CollisionInfo collisionInfo)
{
	if(collisionInfo.isLeftCollision())
	{
		player->setStep(STAND_STEP);
	}	
	if(collisionInfo.isUpCollision())
	{
		player->setGravityFlag(false);
	}	
}

///

/// JumpRightStatus

/// Los siguientes metodos permiten moverse mientras el player est� saltando
void JumpRightStatus::onLeftWalk(Player* player)
{
    player->setStep(WLS_STEP);
    player->setCurrentStatus(new JumpLeftStatus());
    player->runAnimationByCode(JUMP_LEFT_ID);


}

void JumpRightStatus::onRightWalk(Player* player)
{
    player->setStep(WRS_STEP);
}

void JumpRightStatus::onStand(Player* player)
{
    player->setStep(STAND_STEP);
}

void JumpRightStatus::onFall(Player* player)
{
    player->setJumpStep(STAND_STEP);
    player->setCurrentStatus(new FallRightStatus());
    player->runAnimationByCode(FALL_RIGHT_ID);

}

void JumpRightStatus::onCollision(Player* player, CollisionInfo collisionInfo)
{
	if(collisionInfo.isLeftCollision())
	{
		player->setStep(STAND_STEP);
	}	
	if(collisionInfo.isDownCollision())
	{
		player->setJumpStep(STAND_STEP);
		player->resetJumpCycle();
		
		this->onFall(player);
	}
}

///

/// JumpLeftStatus

/// Los siguientes metodos permiten moverse mientras el player est� saltando
void JumpLeftStatus::onLeftWalk(Player* player)
{
    player->setStep(WLS_STEP);
}

void JumpLeftStatus::onRightWalk(Player* player)
{
    player->setStep(WRS_STEP);
    player->setCurrentStatus(new JumpRightStatus());
    player->runAnimationByCode(JUMP_RIGHT_ID);

}

void JumpLeftStatus::onStand(Player* player)
{
    player->setStep(STAND_STEP);
}

void JumpLeftStatus::onFall(Player* player)
{
    player->setJumpStep(STAND_STEP);
    player->setCurrentStatus(new FallLeftStatus());
    player->runAnimationByCode(FALL_LEFT_ID);

     /// Esto permite elegir la animacion correspondiente al caer de un lado u otro...
     /// tambien permite usar una animacion diferente al caer, o realizar alguna accion
     /// particular en ese caso
}

void JumpLeftStatus::onCollision(Player* player, CollisionInfo collisionInfo)
{
	if(collisionInfo.isRightCollision())
	{
		player->setStep(STAND_STEP);
	}	
	if(collisionInfo.isDownCollision())
	{
		player->setJumpStep(STAND_STEP);
		player->resetJumpCycle();
		
		this->onFall(player);
	}
	
}

///

/// FallLeftStatus


void FallLeftStatus::onLeftWalk(Player* player)
{
    player->setStep(WLS_STEP);

}

void FallLeftStatus::onRightWalk(Player* player)
{
    player->setStep(WRS_STEP);

    player->setCurrentStatus(new FallRightStatus());
    player->runAnimationByCode(FALL_RIGHT_ID);

}

void FallLeftStatus::onStand(Player* player)
{
    player->setStep(STAND_STEP);
}

void FallLeftStatus::onLand(Player* player)
{
    player->setCurrentStatus(new StandLeftStatus());
    player->runAnimationByCode(STAND_LEFT_ID);

     if(player->getStep() == WLS_STEP)
         player->getCurrentStatus()->onLeftWalk(player);

}

void FallLeftStatus::onCollision(Player* player, CollisionInfo collisionInfo)
{
	if(collisionInfo.isRightCollision())
	{
		player->setStep(STAND_STEP);
	}	
	if(collisionInfo.isUpCollision())
	{
		player->setGravityFlag(false);
		this->onLand(player);
		
	}	
}

///

/// FallRightStatus


void FallRightStatus::onLeftWalk(Player* player)
{
    player->setStep(WLS_STEP);
    player->setCurrentStatus(new FallLeftStatus());
    player->runAnimationByCode(FALL_LEFT_ID);

}

void FallRightStatus::onRightWalk(Player* player)
{
    player->setStep(WRS_STEP);

}

void FallRightStatus::onStand(Player* player)
{
    player->setStep(STAND_STEP);
}

void FallRightStatus::onLand(Player* player)
{
    player->setCurrentStatus(new StandRightStatus());
    player->runAnimationByCode(STAND_RIGHT_ID);
     if(player->getStep() == WRS_STEP)
         player->getCurrentStatus()->onRightWalk(player);

}

void FallRightStatus::onCollision(Player* player, CollisionInfo collisionInfo)
{
	if(collisionInfo.isLeftCollision())
	{
		player->setStep(STAND_STEP);
	}	
	if(collisionInfo.isUpCollision())
	{
		player->setGravityFlag(false);
		this->onLand(player);
		
	}	
}



///

/// StandLeftAttackStatus



