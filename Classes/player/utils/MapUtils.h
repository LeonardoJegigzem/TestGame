#ifndef _MAP_UTILS_H_
#define _MAP_UTILS_H_

#include <string>

class Status;

class MapUtils
{
public:
    static Status* mapStatus(std::string statusName);
    static std::string mapStatusAttackToMove(std::string statusName);

};

#endif
