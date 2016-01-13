#ifndef _LEVEL_BACKGROUND_H_
#define _LEVEL_BACKGROUND_H_

#include <2d/CCTMXTiledMap.h>
#include <2d/CCTMXLayer.h>


USING_NS_CC;

class LevelBackground : public TMXTiledMap
{

public:
    LevelBackground(std::string tileMapName, std::string metaLayerName, std::string foregroundLayerName);
    Vec2 getTileMapSizeInPixels();
    Vec2 getTileSizeInPixels();

    Vec2 getTileNumberByPosition(Vec2 position);

    TMXLayer* getMetaLayer();
    TMXLayer* getForegroundLayer();

private:
    TMXLayer* _meta;
    TMXLayer* _foreground;
};


#endif // _LEVEL_H_
