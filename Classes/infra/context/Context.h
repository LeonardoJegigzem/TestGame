#ifndef _CONTEXT_H_
#define _CONTEXT_H_

#include "infra/ElemId.h"
#include "level/constants/SizeConstants.h"
#include <2d/CCLayer.h>
#include <string>


USING_NS_CC;

class Player;

class Context
{
public:

    static Context* getInstance();
    static void resetInstance();

    void saveLayer(int layerId, Layer* layer);
    Layer* getLayerByID(int layerId);

    void setLevelMapSize(Vec2 vec);
    const Vec2& getLevelMapSize();

    void setTextureCompressionFormat(std::string tc);
    std::string getTextureCompressionFormat();

	void setTransition(bool transition);
	bool isTransition();
	
	void setCurrentDelta(float delta);
	float getCurrentDelta();

	Player* getCurrentPlayer();
	void setCurrentPlayer(Player* player);

    void setViewpointCenter(Vec2 point);
private:

    void init();

    float _currentDelta;
    Vec2 _screenSize;
    Vec2 _levelMapSize;

    std::string _textureCompression;
	bool _transition;
	
    std::map<int, Layer*> _layerMap;
    Player* _player;

    static Context* _instance;
};


#endif // _CONTEXT_H_
