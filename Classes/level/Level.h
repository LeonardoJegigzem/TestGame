#ifndef _LEVEL_H_
#define _LEVEL_H_

#include "level/LevelBackground.h"
#include "level/LevelElements.h"

class Level
{

public:
    Level(std::string levelName);
    ~Level();
    LevelBackground* getBackground();
    LevelElements* getElements();
	std::string getTransitionName();

private:
	std::string _transitionName;
    LevelBackground* _lvlback; // Contiene el contenido estatico del nivel
    LevelElements* _lvlelems; // Contiene el contenido dinamico del nivel que intereactue con el jugador o NPCs



};


#endif // _LEVEL_H_
