#include "GameLayer.h"

#include "infra/context/Context.h"
#include "infra/ElemId.h"
#include "ZOrder.h"
#include "ConfigConst.h"
#include "level/LevelBackground.h"
#include "level/LevelManager.h"
#include "level/config/LevelConfig.h"
#include "collision/CollisionHandler.h"

/**  FEATURES LIST:
 *
 *
 *	0. Crear factories para la creación de cada uno de los elementos que levanta del archivo de level
 *		Player, Weapon
 *		Terminar las clases NonPlayableCharacter y PlayableCharacter
 *		(En la medida que se vayan mejorando las armas, agregar wrappers para cada tipo de Weapon específica, espada o armas)
 *
 *	1. Agregar animación para las armas, que cada arma se superponga sobre la animación de ataque
 *	   Cada animación de arma va a depender de que arma esté seleccionada.
 *	2. Agregar elementos dinamicos, ya sean plataformas moviles, enemigos, etc.
 * 	3. Agregar las colisiones por boundingBox entre los elementos dinamicos.
 *	4. Agregar una clase para el manejo del parallax del fondo.
 *
 *
 *
 *
 *   REFACTOR LIST:
 ----> Agregar movimiento con inercia.
 * (X,Y) = (X0,Y0) + (V0x,V0y) * Delta + 1/2 (Gx,Gy) Delta^2
 ----> MODIFICAR EL MODO DE CALCULAR LAS POSICIONES DEL SALTO, TIRO OBLICUO! :P

 **    BUGS:
 *		----> Al estar habilitado el seteo dinamico del thumb, obliga a hace touch sobre el thumb para que este se mueva!, deberia tomar el touch directamente!
 *       ----> No se hace la deteccion de finalización del mapa
 *		----> Si los pixeles de Salto no son multiplos de los pixeles de gravedad la colision no funciona
 * 			  Se podria arreglar haciendo que cuando se exceda el tileUpPosition, la posicion del Player se corrija para que su DownPosition quede igual al tileUpPosition!
 *
 *
 *
 *
 *
 *
 */

USING_NS_CC;

GameLayer::~GameLayer()
{
	delete _player;
	_manager->resetInstance();
	Context::getInstance()->resetInstance();

}

Scene* GameLayer::createScene()
{
	auto scene = Scene::create();
	auto gameLayer = GameLayer::create();
	scene->addChild(gameLayer, ZORD_GLAYER);

#ifdef INPUT_VK_ENABLED
	auto joystickLayer = JoystickLayer::create();
	scene->addChild(joystickLayer, ZORD_HUD);
#endif

	return scene;
}

bool GameLayer::init()
{

	CCLOG("Initializing GameLayer...");

	if (!Layer::init())
		return false;

	Context::getInstance()->saveLayer(ID_GLAYER, this);

	_manager = InputFactory::getInputManager();

	this->loadLevelElements(INIT_LEVEL);

	this->scheduleUpdate();

	CCLOG("Initializing GameLayer done.");

	return true;
}

void GameLayer::update(float s)
{

	this->handleInput();
	this->_player->update();

	if (Context::getInstance()->isTransition())
		handleLevelTransition();

	Context::getInstance()->setCurrentDelta(s);
	/// TODO
	/// Iterar sobre un vector de EntityWithMass y llamar el update de cada uno!

}

void GameLayer::setPlayer(Player* player)
{
	this->_player = player;
}

void GameLayer::handleInput()
{
	if (_manager->isRightEvent())
		this->_player->walk(true);

	if (_manager->isLeftEvent())
		this->_player->walk(false);

	if (_manager->isStandEvent())
		this->_player->stand();

	if (_manager->isJumpEvent())
		this->_player->jump();

	if (_manager->isAttackEvent())
		this->_player->attack();

}

void GameLayer::levelCleanup()
{
	this->stopAllActions();
	this->removeChild(_currentLevel->getBackground());

}


void GameLayer::handleLevelTransition()
{
	CCLOG("Level transition detected. next level [%s]",
			_currentLevel->getTransitionName().c_str());

	levelCleanup();
	loadLevelElements(_currentLevel->getTransitionName());

}

void GameLayer::loadLevelElements(std::string levelName)
{
	/* Obtengo el nivel actual */
	CCLOG("Loading data of level %s", levelName.c_str());

	/* Genero el nuevo nivel */
	LevelManager::getInstance()->generateLevelByName(levelName);

	/* Obtengo el nivel instanciado */
	_currentLevel = LevelManager::getInstance()->getLevelByName(levelName);

	LevelBackground* lvlBack = _currentLevel->getBackground();
	LevelElements* lvlElems = _currentLevel->getElements();

	CCLOG("Adding background.");
	this->addChild(lvlBack, ZORD_TMX); //Agrego el tilemap a al scene

	if (_player == NULL)
	{
		CCLOG("Adding player.");
		this->setPlayer(lvlElems->getPlayer()); // Agrego el player

		this->addChild(_player->getAnimationHandler()->getNode()); // Agrego el nodo con la animaci�n actual del player
		this->addChild(_player->getCurrentWeapon()->getAnimationHandler()->getNode());
		Context::getInstance()->setCurrentPlayer(lvlElems->getPlayer()); /// Valor disponible a nivel aplicacion para ser utilizado por los triggers

	}
	Context::getInstance()->setLevelMapSize(lvlBack->getTileMapSizeInPixels());
	CollisionHandler::setMetaLayer(lvlBack->getMetaLayer());
	CollisionHandler::setLevelBackground(lvlBack);

	CCLOG("Loading level done.");
}

/**
 *  Metodos de compresion de texturas:
 *  PVRTC(PowerVR Texture Compression): Soportado en GPUs PowerVR. (.pvr.ccz)
 *  ETC1(Ericsson Texture Compression): Disponible para todas las versiones de Android, no soporta canal alpha. (.pkm)
 *  S3TC(S3 Texture Compression): Soportado en chispet NVIDIA.
 *  ATITC(ATI Texture Compression): Soportado en GPUs Adreno. (.dds)
 **/
