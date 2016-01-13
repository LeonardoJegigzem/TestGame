#include "infra/context/Context.h"

Context* Context::_instance = NULL;

Context* Context::getInstance()
{
    if(_instance == NULL)
    {
        _instance = new Context();
        _instance->init();
    }

    return _instance;
}

void Context::resetInstance()
{
    delete _instance;
    _instance = NULL;
}

void Context::saveLayer(int layerId, Layer* layer)
{
    bool isLoaded = _layerMap.count(layerId);
    if(!isLoaded)
        _layerMap[layerId] = layer;
}

Layer* Context::getLayerByID(int layerId)
{
    return this->_layerMap[layerId];
}

void Context::setLevelMapSize(Vec2 vec)
{
    this->_levelMapSize = vec;
}

const Vec2& Context::getLevelMapSize()
{
    return this->_levelMapSize;
}

void Context::setTextureCompressionFormat(std::string tc)
{
    this->_textureCompression = tc;
}

std::string Context::getTextureCompressionFormat()
{
    return _textureCompression;
}

void Context::setTransition(bool transition)
{
	this->_transition = transition;
}

bool Context::isTransition()
{
	return this->_transition;
}

void Context::setCurrentDelta(float delta)
{
	this->_currentDelta = delta;
}

float Context::getCurrentDelta()
{
	return this->_currentDelta;
}

Player* Context::getCurrentPlayer()
{
	return this->_player;
}

void Context::setCurrentPlayer(Player* player)
{
	this->_player = player;
}

void Context::setViewpointCenter(Vec2 point)
{
    /**
        Seg�n de la posici�n a donde mueve el jugador, mueve el layer la diferencia desde la posici�n incial del jugador a la final
        de manera que siempre acomoda al mismo en el centro de la pantalla
     */
    ///Las cotas corresponden a la mitad del tama�o de la pantalla
    Vec2 cotaInf(_screenSize.x/2, _screenSize.y/2); /// Cota inferior para no scrollear
    Vec2 centerPoint(_screenSize.x/2, _screenSize.y/2); ///Centro del tilemap
    Vec2 cotaSup(_levelMapSize.x - centerPoint.x, _levelMapSize.y - centerPoint.y); /// Cota superior para no scrollear

    Vec2 viewPoint = centerPoint - point; /// Offset de cuanto hay que mover el layer desde la posici�n actual del jugador (Center point)

	Vec2 newPosition = viewPoint;
	
    if(point.x < cotaInf.x)
		newPosition.x = centerPoint.x - cotaInf.x;
	if(point.x > cotaSup.x)
		newPosition.x = centerPoint.x - cotaSup.x;
	
    if(point.y < cotaInf.y)
		newPosition.y = centerPoint.y - cotaInf.y;
	if(point.y > cotaSup.y)
		newPosition.y = centerPoint.y - cotaSup.y;
	
   getLayerByID(ID_GLAYER)->setPosition(newPosition);

}


void Context::init()
{
    this->_screenSize.x = SCREEN_W;
    this->_screenSize.y = SCREEN_H;
}
