#ifndef _ELEMENTS_DESCRIPTOR_H_
#define _ELEMENTS_DESCRIPTOR_H_

#include "thirdparty/rapidxml.hpp"

#include "level/config/descriptors/PlayerDescriptor.h"
#include <string>


/**
*    @class ElementsDescriptor
*    @brief Describe el tag <elements>
*    @author djg
*    @date 11/12/2014
*/
class ElementsDescriptor
{
public:
    ElementsDescriptor(rapidxml::xml_node<>* elements);
    ~ElementsDescriptor();
    PlayerDescriptor* getPlayerInfo();


private:

    PlayerDescriptor* _player = NULL;

};

#endif // _ELEMENTS_DESCRIPTOR_H_
