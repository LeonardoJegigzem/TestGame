#ifndef _ANIMATION_STORE_H_
#define _ANIMATION_STORE_H_

#include "player/AnimationHandler.h"

#include <map>
#include <string>


/* Singleton que contiene todos los animationHandlers, de manera que esten disponibles fuera del elemento en donde están declarados
 * principalmente pensado para poder compartir en AnimationHandler entre los distintos weapons y desacoplar al animación del objeto en si
 * */

class AnimationStore
{
public:
	~AnimationStore();

	static AnimationStore* getInstance();
	static void resetInstance();

	void addNewAnimationContainer(std::string id, std::string atlasName, std::vector<AnimationDescriptor*> animationDescriptorList);
	AnimationHandler* getAnimationContainerById(std::string id);

private:
	AnimationStore(){};
	static AnimationStore* _instance;

	std::map<std::string, AnimationHandler*> _handlersMap;
};


#endif
