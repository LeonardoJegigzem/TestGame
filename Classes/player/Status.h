#ifndef _STATUS_H_
#define _STATUS_H_

#include "cocos2d.h"
#include "player/constants/StatusId.h"
#include "collision/CollisionInfo.h"

class Player;

class Status
{

public:
    Status(){};
    Status(std::string status);
    virtual ~Status(){}

    void setStatusDescription(std::string status);
    std::string getStatusDescription();

    void onWalk(int orientation, Player* player);

    virtual void onLeftWalk(Player* player){};
    virtual void onRightWalk(Player* player){};
    virtual void onStand(Player* player){}; /// Cuando el jugador no realiza ninguna accion
    virtual void onJump(Player* player){};
    virtual void onFall(Player* player){}; /// Al comenzar a caer luego de terminado el ciclo de salto
    virtual void onLand(Player* player){}; /// Al colisionar con un tile que corresponda al suelo
	virtual void onCollision(Player* player, CollisionInfo collisionInfo){};
	virtual void onAttack(Player* player){}; /// Segun es estado en el que este, decido que tipo de ataque estoy realizando (en Jump, Walk o Stand)
	
    enum status_orientation {TOLEFT=0, TORIGHT};


protected:
    std::string _statusDescription;

};

///

class StandLeftStatus : public Status
{
public:
    StandLeftStatus() : Status(STAND_LEFT_ID){};
    void onLeftWalk(Player* player) override;
    void onRightWalk(Player* player) override;
    void onJump(Player* player) override;
	void onCollision(Player* player, CollisionInfo collisionInfo) override;
	void onAttack(Player* player) override;

};

class StandRightStatus : public Status
{
public:
    StandRightStatus() : Status(STAND_RIGHT_ID){};
    void onLeftWalk(Player* player) override;
    void onRightWalk(Player* player) override;
    void onJump(Player* player) override;
	void onCollision(Player* player, CollisionInfo collisionInfo) override;
	void onAttack(Player* player) override;

};


class WalkLeftStatus : public Status
{
public:
    WalkLeftStatus() : Status(WALK_LEFT_ID){};
    void onRightWalk(Player* player) override;
    void onJump(Player* player) override;
    void onStand(Player* player) override;
	void onFall(Player* player) override;
	void onCollision(Player* player, CollisionInfo collisionInfo) override;


};

class WalkRightStatus : public Status
{
public:
    WalkRightStatus() : Status(WALK_RIGHT_ID){};
	void onLeftWalk(Player* player) override;
    void onJump(Player* player) override;
    void onStand(Player* player) override;
	void onFall(Player* player) override;
	void onCollision(Player* player, CollisionInfo collisionInfo) override;

};

class JumpRightStatus : public Status
{
public:
    JumpRightStatus() : Status(JUMP_RIGHT_ID){};
    void onLeftWalk(Player* player) override;
    void onRightWalk(Player* player) override;
    void onStand(Player* player) override;
    void onFall(Player* player) override;
	void onCollision(Player* player, CollisionInfo collisionInfo) override;


};


class JumpLeftStatus : public Status
{
public:
    JumpLeftStatus() : Status(JUMP_LEFT_ID){};
    void onLeftWalk(Player* player) override;
    void onRightWalk(Player* player) override;
    void onStand(Player* player) override;
    void onFall(Player* player) override;
	void onCollision(Player* player, CollisionInfo collisionInfo) override;


};



class FallRightStatus : public Status
{
public:
    FallRightStatus() : Status(FALL_RIGHT_ID){};
    void onLeftWalk(Player* player) override;
    void onRightWalk(Player* player) override;
    void onStand(Player* player) override;
    void onLand(Player* player) override;
	void onCollision(Player* player, CollisionInfo collisionInfo) override;


};


class FallLeftStatus : public Status
{
public:
    FallLeftStatus() : Status(FALL_LEFT_ID){};
    void onLeftWalk(Player* player) override;
    void onRightWalk(Player* player) override;
    void onStand(Player* player) override;
    void onLand(Player* player) override;
	void onCollision(Player* player, CollisionInfo collisionInfo) override;


};


/* ATTACK STATUS */

class WalkLeftAttackStatus : public WalkLeftStatus
{
public:
	WalkLeftAttackStatus() : WalkLeftStatus(){};
	
};


class WalkRightAttackStatus : public WalkRightStatus
{
public:
	WalkRightAttackStatus() : WalkRightStatus(){};
};


class StandLeftAttackStatus : public StandLeftStatus
{
public:
	StandLeftAttackStatus() : StandLeftStatus(){};

};


class StandRightAttackStatus : public StandRightStatus
{
public:
	StandRightAttackStatus() : StandRightStatus(){};
};

#endif // _STATUS_H_
