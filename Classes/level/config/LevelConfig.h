#ifndef _LEVEL_CONFIG_H_
#define _LEVEL_CONFIG_H_

#include "cocos2d.h"
#include "thirdparty/rapidxml.hpp"

#include "level/config/descriptors/BackgroundDescriptor.h"
#include "level/config/descriptors/ElementsDescriptor.h"

#define LVL_EXT ".xml"

USING_NS_CC;

/**
*    @class LevelConfig
*    @brief Describe el root <level-config> e incializa la carga de los xml de nivel.
*    @author djg
*    @date 11/12/2014
*/
class LevelConfig
{

public:
    LevelConfig(std::string fileName);
    ~LevelConfig();

    BackgroundDescriptor* getBackground();
    ElementsDescriptor* getElements();

	std::string getTransitionName();
private:

    void initialize(std::string fileName);

    rapidxml::xml_document<> _doc; /* Contiene el archivo de nivel seleccionado en el constructor */

    BackgroundDescriptor* _back; /* Describe el tag background */
    ElementsDescriptor* _elems; /* Describe el tag elements */
	
	std::string _transitionName; /* Contiene el nombre de la transicion a realizar desde el nivel actual */

};


#endif // _LEVEL_CONFIG_H_
