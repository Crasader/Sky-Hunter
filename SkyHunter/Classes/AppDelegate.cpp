#include "AppDelegate.h"
#include "GameLayer.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("Sky Hunter");
        director->setOpenGLView(glview);
    }

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	glview->setFrameSize(480, 854);//sony xeria u
	//glview->setFrameSize(DESING_WIDTH,DESING_HEIGHT);
#endif

	glview->setDesignResolutionSize(DESING_WIDTH, DESING_HEIGHT, ResolutionPolicy::EXACT_FIT);

    register_all_packages();

	//load sounds
	SimpleAudioEngine::getInstance()->
		preloadEffect(FileUtils::getInstance()->fullPathForFilename("music/explosion.wav").c_str());

	SimpleAudioEngine::getInstance()->
		preloadBackgroundMusic(FileUtils::getInstance()->fullPathForFilename("music/game_loop.mp3").c_str());
	SimpleAudioEngine::getInstance()->
		preloadEffect(FileUtils::getInstance()->fullPathForFilename("music/Laser_Shoot6.wav").c_str());

	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.4f);
	SimpleAudioEngine::getInstance()->setEffectsVolume(1.0f);

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
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
