#ifndef _LEVEL_MANAGER_H_
#define _LEVEL_MANAGER_H_

#include "level/Level.h"

class LevelManager
{
public:

    ~LevelManager();
    void generateLevelByName(std::string name);
    void generateLevelsByPattern(std::string pattern, int nLevels);
    Level* getLevelByName(std::string name);
    static LevelManager* getInstance();
    static void resetInstance();

private:

    LevelManager(){};

    std::map<std::string, Level*> _levelMap;
    static LevelManager* _instance;
};


#endif // _LEVEL_MANAGER_H_
