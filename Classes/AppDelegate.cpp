#include "AppDelegate.h"
#include "GameLayer.h"
#include "ConfigConst.h"

#include "level/LevelManager.h"
#include "infra/graphics/GPU_TC.h"
#include "infra/graphics/ResolutionSupport.h"
#include "infra/context/Context.h"


USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("Proof of concept");
        director->setOpenGLView(glview);
    }

    ///Escala el contenido en pantalla segun una resolucion de dise�o base
    ///de manera que el contenido que se ve en al resolucion original, se va a mantener en diferentes resoluciones

    ResolutionSupport::setScalingResolution(glview); ///  Probar si esto funciona en dispositivos de mayor resolucion!

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // Obtain the texture compression in use according the GPU
///    std::string TC = getTC(); //COMENTADO HASYA HACER LAS DEMAS VERSIONES DEL NUEVO SPRITE!

    Context::getInstance()->setTextureCompressionFormat(".png");
    CCLOG("Using %s as texture compression format.", Context::getInstance()->getTextureCompressionFormat().c_str());

    //Initialize all the levels configuration before loading the scene
   // LevelManager::getInstance()->generateLevelsByPattern(LEVEL_NAME_PATTERN, N_LEVELS);
    /// TODO: Hacer esto on demand, que no se carguen todos los niveles juntos!
    /// que la "GameLayer" se encarge de manejar el flujo de los niveles y delegue la carga en el SceneLoader
    /// de momento no importa, pero para m�s adelante! :P


    // create a scene. it's an autorelease object
    auto scene = GameLayer::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
