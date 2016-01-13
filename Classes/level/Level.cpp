#include "level/Level.h"
#include "level/config/LevelConfig.h"
#include "infra/ResPathConstants.h"

Level::Level(std::string levelName)
{
    CCLOG("Generating level %s...", levelName.c_str());
    LevelConfig config(LEVEL_CONFIG_PATH + levelName);

    CCLOG("Generating background...");
    this->_lvlback = new LevelBackground(LEVEL_TMX_PATH + config.getBackground()->getTMX(), config.getBackground()->getMetaLayerName(), config.getBackground()->getForegroundLayerName());

    CCLOG("Generating elements...");
    this->_lvlelems = new LevelElements(config.getElements());
	
	this->_transitionName = config.getTransitionName();

    CCLOG("Level generated.");

}

Level::~Level()
{
    delete this->_lvlback;
    delete this->_lvlelems;
}


LevelBackground* Level::getBackground()
{
    return this->_lvlback;
}

LevelElements* Level::getElements()
{
    return this->_lvlelems;
}

std::string Level::getTransitionName()
{
	return this->_transitionName;
}
