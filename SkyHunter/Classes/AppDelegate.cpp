#include "AppDelegate.h"
#include "MainMenuLayer.h"
#include "CustomAudioManager.h"


USING_NS_CC;
using namespace Levels;
using namespace Menus;

AppDelegate::AppDelegate() 
{
}

AppDelegate::~AppDelegate()  
{
}


void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}


static int register_all_packages()
{
    return 0;
}

bool AppDelegate::applicationDidFinishLaunching() {
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("Sky Hunter");
        director->setOpenGLView(glview);
    }

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	glview->setFrameSize(480, 854);//sony xeria u
#endif

	glview->setDesignResolutionSize(DESING_WIDTH, DESING_HEIGHT, ResolutionPolicy::EXACT_FIT);

    register_all_packages();

	CustomAudioManager::getInstance()->preloadBackground("music/Cetus.wav");
	CustomAudioManager::getInstance()->preloadBackground("music/Lensko.wav");
	CustomAudioManager::getInstance()->preloadEffect("music/hit.wav");
	CustomAudioManager::getInstance()->preloadEffect("music/laser_shoot.wav");
	CustomAudioManager::getInstance()->preloadEffect("music/explosion.wav");


	auto mainScene = MainMenuLayer::createScene();
	director->runWithScene(mainScene);

    return true;
}

void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // pausa la musica
	CustomAudioManager::getInstance()->pauseAll();

	
}


void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

	//resume la musica
	CustomAudioManager::getInstance()->resumeAll();
}
