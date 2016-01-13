#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"
#include "player/Player.h"
#include "input/util/InputFactory.h"
#include "input/InputManager.h"
#include "hud/JoystickLayer.h"
#include "level/Level.h"


USING_NS_CC;

class GameLayer : public cocos2d::Layer
{

public:

    ~GameLayer();
    static cocos2d::Scene* createScene();
    CREATE_FUNC(GameLayer);
    virtual bool init();

    void setPlayer(Player* player);

    void update(float s = 0);

private:


	void handleInput();
	void handleLevelTransition(); // Se encarga de realizar la transicion del nivel segun indica la configuracion
	
	void levelCleanup();
    void loadLevelElements(std::string levelName);
	
	
    Player* _player = NULL;
    InputManager* _manager;
	Level* _currentLevel;
};

#endif //__GAME_LAYER_H__
