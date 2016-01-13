#ifndef _LEVEL_ELEMENTS_H_
#define _LEVEL_ELEMENTS_H_

#include "level/config/descriptors/ElementsDescriptor.h"
#include "player/Player.h"

class LevelElements
{
public:
    LevelElements(ElementsDescriptor* elements);
	~LevelElements();
    Player* getPlayer();
private:

    void generatePlayer(PlayerDescriptor* player);

   Player* _player;
};



#endif // _LEVEL_ELEMENTS_H_
