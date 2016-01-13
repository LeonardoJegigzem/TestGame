#include "level/config/descriptors/BackgroundDescriptor.h"
#include "level/util/LevelConfigMacros.h"

BackgroundDescriptor::BackgroundDescriptor(rapidxml::xml_node<>* background)
{
    this->_tmxAttr = NotNull(background->first_attribute("tmx"));
    this->_metaLayer = NotNull(background->first_attribute("metalayer"));
    this->_foregroundLayer = NotNull(background->first_attribute("foregroundlayer"));
}


std::string BackgroundDescriptor::getTMX()
{
    return this->_tmxAttr;
}

std::string BackgroundDescriptor::getMetaLayerName()
{
    return this->_metaLayer;
}

std::string BackgroundDescriptor::getForegroundLayerName()
{
    return this->_foregroundLayer;
}
