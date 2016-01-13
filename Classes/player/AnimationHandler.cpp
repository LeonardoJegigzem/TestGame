#include "player/AnimationHandler.h"

#include "player/triggers/Trigger.h"

AnimationHandler::AnimationHandler(std::string textureFileName, std::vector<AnimationDescriptor*> nameFramesPair)
{
    CCLOG("AnimationHandler::AnimationHandler initialized");

    std::string fullFileName = textureFileName + TC_EXT; // Segun el tipo de textura
    std::string fullDataName = textureFileName + TC_EXT + DATA_EXT; // TC_EXT.plist

    this->_node = SpriteBatchNode::create(fullFileName.c_str());

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(fullDataName.c_str());

    this->generateAnimations(nameFramesPair);


    CCLOG("AnimationHandler::AnimationHandler done.");
}

AnimationHandler::~AnimationHandler()
{
    for(auto &elem : _actions)
    {
        elem.second->release();
    }
}

void AnimationHandler::generateAnimations(std::vector<AnimationDescriptor*> animationList)
{
    CCLOG("AnimationHandler::generateAnimations initialized");
    CCLOG("=Generating animations objects.");

    int animCount = animationList.size();
    Vector<SpriteFrame*>* vectorBuffer = new Vector<SpriteFrame*>[animCount];
    for(int c = 0; c < animCount;c++)
    {
        auto elem = animationList.at(c);

        std::string pattern = elem->getPattern();
        int frameCount = elem->getFrameCount();
        float speed = elem->getAnimationSpeed() == 0? DEFAULT_SPEED : elem->getAnimationSpeed();
        std::string status = elem->getStatus();
        this->loadFrameBuffer(vectorBuffer[c], frameCount, pattern);

        _animations.push_back(Animation::createWithSpriteFrames(vectorBuffer[c], speed));
        _actions[status] = generateAction(elem, _animations.at(c));
        _actions[status]->retain();
    }

    delete[] vectorBuffer;

    CCLOG("AnimationHandler::generateAnimations done.");

}

FiniteTimeAction* AnimationHandler::generateAction(AnimationDescriptor* descriptor, Animation* animation)
{
	std::string animationType = descriptor->getAnimationType();
	std::string status = descriptor->getStatus();

	if(animationType == "once")
	{
		return Repeat::create(Animate::create(animation), 1);
	}
	else if(animationType == "once-sequenced")
	{
		auto func = CallFunc::create([=]()
		{
			/// Indico es status de ataque que tiene que ser swappeado al status de movimiento
			StatusTrigger::swapStatus(status);
		});

		return Sequence::create(Repeat::create(Animate::create(animation), 1), func, nullptr);
	}
	else
	{
		return RepeatForever::create(Animate::create(animation));
	}

}

void AnimationHandler::loadFrameBuffer(Vector<SpriteFrame*> &frameBuffer, int nElem, std::string pattern)
{
    CCLOG("AnimationHandler::loadFrameBuffer initialized");
    char str[50];
    frameBuffer = Vector<SpriteFrame*>(nElem);
    CCLOG("*Buffer capacity is [%zd].", frameBuffer.capacity());
    for(int counter = 1; counter <= nElem; counter++)
    {
        sprintf(str, pattern.c_str(), counter);
        CCLOG("=Loading frame with key[%s].", str);
        frameBuffer.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(str));
    }

    CCLOG("*Buffer loaded with [%zd] elements.", frameBuffer.size());
    CCLOG("AnimationHandler::loadFrameBuffer done.");

}

SpriteBatchNode* AnimationHandler::getNode()
{
    return _node;
}

Animation* AnimationHandler::getAnimationByCode(int code)
{
    return _animations.at(code);
}


FiniteTimeAction* AnimationHandler::getActionByKey(std::string key)
{
    return _actions[key];
}
