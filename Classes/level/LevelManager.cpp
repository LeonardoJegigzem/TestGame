#include "level/LevelManager.h"

LevelManager* LevelManager::_instance = NULL;

LevelManager* LevelManager::getInstance()
{
    if(_instance == NULL)
        _instance = new LevelManager();
    return _instance;
}

void LevelManager::resetInstance()
{
    delete _instance;
    _instance = NULL;
}

LevelManager::~LevelManager()
{
    for(auto& levelPair:_levelMap)
        delete levelPair.second;
}

void LevelManager::generateLevelByName(std::string name)
///Cada nombre corresponde a un LevelDescriptor, a partir de ese nombre carga el background y los elementos asociados al mismo
{
    bool isLoaded = _levelMap.count(name);
    if(!isLoaded)
        _levelMap[name] = new Level(name);


}

void LevelManager::generateLevelsByPattern(std::string pattern, int nLevels) ///Level_0.... Level_n
{
    char str[50];
    for(int counter = 1; counter <= nLevels; counter++)
    {
        sprintf(str, pattern.c_str(), counter);
        generateLevelByName(str);
    }

}

Level* LevelManager::getLevelByName(std::string name)
{
    return this->_levelMap[name];
}
