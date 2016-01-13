#ifndef _ANIMATION_HANDLER_H_
#define _ANIMATION_HANDLER_H_

#include "cocos2d.h"
#include "infra/context/Context.h"
#include "level/config/descriptors/AnimationDescriptor.h"

#define DATA_EXT ".plist"
#define TC_EXT Context::getInstance()->getTextureCompressionFormat()
#define DEFAULT_SPEED 0.2f

USING_NS_CC;

class AnimationHandler
{

public:

    AnimationHandler(){};
    ~AnimationHandler();
    AnimationHandler(std::string textureFileName,  std::vector<AnimationDescriptor*> nameFramesPair);

    SpriteBatchNode* getNode();

    Animation* getAnimationByCode(int code);
    FiniteTimeAction* getActionByKey(std::string key);

protected:
    void generateAnimations(std::vector<AnimationDescriptor*> animationList); // Este método permite agregar animaciones

private:
    void loadFrameBuffer(Vector<SpriteFrame*> &frameBuffer, int nElem, std::string pattern);


    FiniteTimeAction* generateAction(AnimationDescriptor* desciptor, Animation* animation);

    SpriteBatchNode* _node;
    std::vector<Animation*> _animations;
    std::map<std::string, FiniteTimeAction*> _actions;

};


#endif // _ANIMATION_HANDLER_H_
