#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "cocos2d.h"
#include "player/AnimationHandler.h"
#include "infra/context/Context.h"
#include "util/common/UtilMacros.h"
#include "entity/Entity.h"
#include "player/animation/AnimatedInterface.h"

#include "level/config/descriptors/AnimationsDescriptor.h"
#include "character/weapon/Weapon.h"


USING_NS_CC;

class Status;

class Player : public EntityWithMass, public AnimatedInterface
{
public:
	virtual ~Player();
    virtual void walk(int orientation) = 0;
    virtual void stand() = 0;
    virtual void jump() = 0;
    virtual void step() = 0;
	virtual void move() = 0;
	virtual void attack() = 0;
    void update() override;

    virtual Weapon* getCurrentWeapon() = 0;

    Vec2 getStep();
    void setStep(Vec2 pos);

    Vec2 getJumpStep();
    void setJumpStep(Vec2 pos);
	
	Vec2 getAttemptStep();
	void setAttemptStep(Vec2 pos);

    Status* getCurrentStatus();
    void setCurrentStatus(Status* status, bool release=true);
	
	void resetJumpCycle();

protected:

    Status* _currentStatus;
    Vec2 _step;
    Vec2 _jumpStep;
	
	Vec2 _attemptStep;
	
	 int _cycles;

};

class ScrollingPlayer : public Player
{

public:
    ScrollingPlayer(std::string status, std::string animation, Vec2 position, std::map<std::string, AnimationsDescriptor*> animations);
	ScrollingPlayer(std::string status, Vec2 position);
    ~ScrollingPlayer();

    void walk(int orientation); // Setea el estado que corresponde a caminar.
    void stand() override;
    void jump() override;
    void step() override;
    void collision() override;
	void move() override;
	void attack() override;

    void setCurrentAnimation(std::string animId);
    std::string getCurrentAnimation();

    AnimationHandler* getAnimationHandler() override;

    void setPlayerFrameByNameInCache(std::string name);
    void runAnimationByCode(std::string key) override;

    void setPosition(const Vec2& position) override;

protected:
    void loadAnimationHandler(std::string animId, std::string atlasPath, std::vector<AnimationDescriptor*> descriptorVec);

private:

    std::string _currentAnimation;
    std::map<std::string, AnimationHandler*> _animIdHandler;

   
};


#endif // _PLAYER_H_
