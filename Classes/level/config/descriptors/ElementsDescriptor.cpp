#include "level/config/descriptors/ElementsDescriptor.h"
#include "level/util/LevelConfigMacros.h"

ElementsDescriptor::ElementsDescriptor(rapidxml::xml_node<>* elements)
{
	
    rapidxml::xml_node<>* player = NotNullTag(elements->first_node("player"));
	
	this->_player = new PlayerDescriptor(player);
	
}

ElementsDescriptor::~ElementsDescriptor()
{
    delete this->_player;
}


PlayerDescriptor* ElementsDescriptor::getPlayerInfo()
{

    return this->_player;
}
