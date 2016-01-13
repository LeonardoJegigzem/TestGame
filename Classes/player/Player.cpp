#include "player/Player.h"
#include "player/Status.h"
#include "player/utils/MapUtils.h"
#include "player/constants/MovConstants.h"
#include "player/constants/StatusId.h"
#include "collision/CollisionHandler.h"
#include "collision/CollisionInfo.h"
#include "infra/ResPathConstants.h"

#include "player/animation/AnimationStore.h"

 Player::~Player()
 {
	 delete _currentStatus;
 }

void Player::update()
{
	this->setGravityFlag(true);
	this->step();
	this->collision();
	this->move();

}


/// Setters/Getters
void Player::setCurrentStatus(Status* status, bool release)
{
    if(release)
        delete this->_currentStatus;
    this->stopAllActions();
    this->_currentStatus = status;
}

Status* Player::getCurrentStatus()
{
    return this->_currentStatus;
}

Vec2 Player::getStep()
{
    return this->_step;
}

void Player::setStep(Vec2 pos) ///Llamado por cada Status!
{
    this->_step = pos;
}

Vec2 Player::getJumpStep()
{
    return this->_jumpStep;
}

void Player::setJumpStep(Vec2 pos) ///Llamado por cada Status!
{
    this->_jumpStep = pos;
}

Vec2 Player::getAttemptStep()
{
	return this->_attemptStep;
}

void Player::setAttemptStep(Vec2 pos)
{
	this->_attemptStep = pos;
}

void Player::resetJumpCycle()
{
	this->_cycles = 0;
}


/// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
ScrollingPlayer::ScrollingPlayer(std::string status, std::string animation, Vec2 position, std::map<std::string, AnimationsDescriptor*> animations)
{
    _cycles = 0;
    CCLOG("Generating Player...");
    Sprite::setPosition(position);

    CCLOG("Generating animationHandlers...");
    for(auto &animPair : animations)
    {
        CCLOG("Loading animation descriptors...");
        AnimationsDescriptor* descriptor = animPair.second;
        this->loadAnimationHandler(animPair.first, descriptor->getAtlasPath(), descriptor->getAnimationList());
        //AnimationStore::getInstance()->addNewAnimationContainer(animPair.first,descriptor->getAtlasPath(), descriptor->getAnimationList());
    }

    this->_currentStatus = MapUtils::mapStatus(status);
    this->_currentAnimation = animation;

    this->init();


    this->_animIdHandler[animation]->getNode()->addChild(this, 1);
    //AnimationStore::getInstance()->getAnimationContainerById(animation)->getNode()->addChild(this, 1);
    this->runAnimationByCode(status);

    CCLOG("Player generated.");
}

ScrollingPlayer::ScrollingPlayer(std::string status, Vec2 position)
{
	this->_currentStatus = MapUtils::mapStatus(status);
	Sprite::setPosition(position);
}

ScrollingPlayer::~ScrollingPlayer()
{
    delete this->_currentStatus;
    for(auto &handler : _animIdHandler)
    {
        delete handler.second;
    }
}


void ScrollingPlayer::setCurrentAnimation(std::string animId)
{
    this->_currentAnimation = animId;
}

std::string ScrollingPlayer::getCurrentAnimation()
{
    return this->_currentAnimation;
}


AnimationHandler* ScrollingPlayer::getAnimationHandler()
{
//    return _animHandler;
    return this->_animIdHandler[getCurrentAnimation()];
	//return AnimationStore::getInstance()->getAnimationContainerById(getCurrentAnimation());
}
///

void ScrollingPlayer::setPlayerFrameByNameInCache(std::string name)
{
    this->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name.c_str()));
}

void ScrollingPlayer::runAnimationByCode(std::string key)
{
    this->runAction(this->getAnimationHandler()->getActionByKey(key));
}

void ScrollingPlayer::walk(int orientation)
{

    this->_currentStatus->onWalk(orientation, this);

}

void ScrollingPlayer::stand()
{
    this->_currentStatus->onStand(this);
}

void ScrollingPlayer::jump()
{
    this->_currentStatus->onJump(this);
}

void ScrollingPlayer::step()
{
	this->setAttemptStep(this->getPosition() + _step + _jumpStep); //Indico cual es la posición deseada a mover

}

void ScrollingPlayer::move()
{
	this->setPosition(this->getPosition() + _step + _jumpStep);

    if(_currentStatus->getStatusDescription() == JUMP_LEFT_ID ||
        _currentStatus->getStatusDescription() == JUMP_RIGHT_ID) /// Si estoy saltando incremento el conteo de ciclos de salto
    {
        _cycles++;
    }

	if((_currentStatus->getStatusDescription() == WALK_LEFT_ID ||
		_currentStatus->getStatusDescription() == WALK_RIGHT_ID) && this->hasGravity()) /// Si WL o WR y comienzo a caer, ejecuto la accion en onFall
	{
		this->_currentStatus->onFall(this);
	}

    if(_cycles == JMP_LOW_CYCLE)
    {
        this->_currentStatus->onFall(this);
         _cycles = 0;
    }
}

void ScrollingPlayer::attack()
{
	this->_currentStatus->onAttack(this);
}

void ScrollingPlayer::collision()
{
	if(this->isCollisionable()) /* Este if seguramente tenga que estar en una clase superior ya que no aplica solo al ScrollingPlayer */
	{
		CollisionInfo info = CollisionHandler::getCollisionInfo(this->getCurrentStatus()->getStatusDescription(), this->getAttemptStep());
		//Valido la colision teniendo en cuenta la posicion a la cual pretendo moverme
		this->_currentStatus->onCollision(this, info);

		Context::getInstance()->setTransition(info.isTransition());
		///TODO Respuesta de cada Entity a las colisiones!
	}
}

void ScrollingPlayer::setPosition(const Vec2& position)
{
    EntityWithMass::setPosition(position);
    Context::getInstance()->setViewpointCenter(position);


}

void ScrollingPlayer::loadAnimationHandler(std::string animId, std::string atlasPath, std::vector<AnimationDescriptor*> descriptorVec)
{
	/// Si hay un atlas path definido lo utilizo, si no uso el animId como atlas.
	std::string atlasFile = atlasPath != ""? atlasPath : animId;

    this->_animIdHandler[animId] = new AnimationHandler(TEXTURE_PATH + atlasFile, descriptorVec);
    CCLOG("Instantiated animationHandler...");

}





