#include "player/animation/AnimationStore.h"
#include "infra/ResPathConstants.h"
#include "base/ccMacros.h"

AnimationStore* AnimationStore::_instance = NULL;

AnimationStore* AnimationStore::getInstance()
{
	if(_instance == NULL)
		_instance = new AnimationStore();

	return _instance;
}

AnimationStore::~AnimationStore()
{
	for(auto &pair: _handlersMap)
	{
		delete pair.second;
	}
	_handlersMap.clear();
}

void AnimationStore::resetInstance()
{

	delete _instance;
	_instance = NULL;
}

void AnimationStore::addNewAnimationContainer(std::string id, std::string atlasName, std::vector<AnimationDescriptor*> animationDescriptorList)
{

	bool isLoaded = _handlersMap.count(id);
	if(!isLoaded)
	{
		CCLOG("AnimationStore::addNewAnimationContainer. Adding new container with data[%s, %s]", id.c_str(), atlasName.c_str());
		this->_handlersMap[id] = new AnimationHandler(TEXTURE_PATH + atlasName, animationDescriptorList);
	}
}

AnimationHandler* AnimationStore::getAnimationContainerById(std::string id)
{
	CCLOG("AnimationStore::getAnimationContainerById. Getting Id : %s", id.c_str());
	return this->_handlersMap[id];
}
