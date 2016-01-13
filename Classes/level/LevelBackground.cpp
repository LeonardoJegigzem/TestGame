#include "level/LevelBackground.h"

LevelBackground::LevelBackground(std::string tileMapName, std::string metaLayerName, std::string foregroundLayerName)
{
    this->initWithTMXFile(tileMapName + ".tmx");

    CCLOG("%s layer setted as meta.", metaLayerName.c_str());

    _meta = this->getLayer(metaLayerName);
    _meta->setVisible(false);

    _foreground = this->getLayer(foregroundLayerName);
}

Vec2 LevelBackground::getTileMapSizeInPixels()
{
    return Vec2(this->getMapSize().width * this->getTileSize().width, this->getMapSize().height * this->getTileSize().height);
}

Vec2 LevelBackground::getTileSizeInPixels()
{
    return Vec2(this->getTileSize().width, this->getTileSize().height);
}

Vec2 LevelBackground::getTileNumberByPosition(Vec2 position)
{
    Vec2 tileSize = this->getTileSizeInPixels();
    return Vec2(int(position.x / tileSize.x),
                int(this->getMapSize().height - (position.y / tileSize.y))); //Se reta el alto del tilemap para invertir el orden
}

TMXLayer* LevelBackground::getMetaLayer()
{
    return this->_meta;
}

TMXLayer* LevelBackground::getForegroundLayer()
{
    return this->_foreground;
}
