#include "level/config/LevelConfig.h"
#include "platform/CCFileUtils.h"
#include "level/util/LevelConfigMacros.h"

LevelConfig::LevelConfig(std::string fileName)
{
    initialize(fileName);

    CCLOG("LevelConfig:: Parsing level file.");

    rapidxml::xml_node<>* levelRoot = this->_doc.first_node("level-config");

	this->_transitionName = NotNull(levelRoot->first_attribute("transition-to"));
	
	CCLOG("LevelConfig:: Generating BackgroundDescriptor...");
	rapidxml::xml_node<>* background = NotNullTag(levelRoot->first_node("background"));
    this->_back = new BackgroundDescriptor(background);
	
	CCLOG("LevelConfig:: Generating ElementsDescriptor...");
	rapidxml::xml_node<>* elements = NotNullTag(levelRoot->first_node("elements"));
    this->_elems = new ElementsDescriptor(elements);

     CCLOG("LevelConfig:: Level parsed successfully.");

}

LevelConfig::~LevelConfig()
{
    delete this->_back;
    delete this->_elems;
}

BackgroundDescriptor* LevelConfig::getBackground()
{
    return this->_back;
}

ElementsDescriptor* LevelConfig::getElements()
{
    return this->_elems;
}

std::string LevelConfig::getTransitionName()
{
	return this->_transitionName;
}

void LevelConfig::initialize(std::string fileName)
{
    CCLOG("LevelConfig:: Loading level file %s.", fileName.c_str());
    std::string file = FileUtils::getInstance()->getStringFromFile(fileName + LVL_EXT);
    std::vector<char> xml_copy(file.begin(), file.end());
    xml_copy.push_back('\0');

    this->_doc.parse<0>(&xml_copy[0]);
    CCLOG("LevelConfig:: Loading level file %s finished.", fileName.c_str());
}
