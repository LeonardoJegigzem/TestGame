#ifndef _BACKGROUND_DESCRIPTOR_H_
#define _BACKGROUND_DESCRIPTOR_H_

#include "thirdparty/rapidxml.hpp"

#include <string>
/**
*    @class BackgroundDescriptor
*    @brief Describe el tag <background>
*    @author djg
*    @date 09/12/2014
*/
class BackgroundDescriptor
{
public:
    BackgroundDescriptor(rapidxml::xml_node<>* background);

    std::string getTMX();
    std::string getMetaLayerName();
    std::string getForegroundLayerName();

private:
    std::string _tmxAttr;
    std::string _metaLayer;
    std::string _foregroundLayer;
};



#endif // _BACKGROUND_DESCRIPTOR_H_

