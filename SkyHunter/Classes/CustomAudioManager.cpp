#include "CustomAudioManager.h"
#include "cocos2d.h"
#include "AudioEngine.h"
#include "SimpleAudioEngine.h"
#include "GameManager.h"


USING_NS_CC;
using namespace CocosDenshion;

CustomAudioManager* CustomAudioManager::_instance = nullptr;

CustomAudioManager::CustomAudioManager()
{
}


CustomAudioManager* CustomAudioManager::getInstance(){
	if (_instance == nullptr) {
		_instance = new CustomAudioManager();
	}
	return _instance;
}

void CustomAudioManager::playEffect(const std::string& filename, bool loop){
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	//just for debug use this in win32
	std::string name = filename.substr(0, filename.find(".")); 
	experimental::AudioEngine::play2d(name+".mp3", loop, GameManager::getInstance()->getEffectsVolume()*0.01); 

#else
	SimpleAudioEngine::getInstance()->setEffectsVolume(GameManager::getInstance()->getEffectsVolume()*0.01);
	SimpleAudioEngine::getInstance()->playEffect(filename.c_str(), loop);
#endif
}

void CustomAudioManager::playBackgroundSound(const std::string& filename, bool loop){
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	//just for debug use this in win32
	std::string name = filename.substr(0, filename.find(".")); 
	experimental::AudioEngine::play2d(name+".mp3", loop, GameManager::getInstance()->getEffectsVolume()*0.01); 
	
#else
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(GameManager::getInstance()->getBgVolume()*0.01);
	SimpleAudioEngine::getInstance()->playBackgroundMusic(filename.c_str(), loop);
#endif
}

void CustomAudioManager::preloadEffect(const std::string& filename){
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32 
	SimpleAudioEngine::getInstance()->preloadEffect(filename.c_str());
#endif

}

void CustomAudioManager::preloadBackground(const std::string& filename){
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32 
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(filename.c_str());

#endif
}


void CustomAudioManager::resumeAll(){
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	experimental::AudioEngine::resumeAll();
#else
	SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	SimpleAudioEngine::getInstance()->resumeAllEffects();
#endif
}

void CustomAudioManager::pauseAll(){
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	experimental::AudioEngine::pauseAll();
#else
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	SimpleAudioEngine::getInstance()->pauseAllEffects();
#endif
}

void CustomAudioManager::stopAll(){
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 
	experimental::AudioEngine::stopAll();
#else
	SimpleAudioEngine::getInstance()->stopAllEffects();
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
#endif
	
	
}