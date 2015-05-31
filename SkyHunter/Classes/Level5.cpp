#include "Level5.h"
#include "CustomAudioManager.h"
#include "Blizzard.h"

USING_NS_CC;

Level5::~Level5(){
	CC_SAFE_RELEASE(_cloudsScheduler);
}

Scene* Level5::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	// 'layer' is an autorelease object
	auto layer = Level5::create();
	// add layer as a child to scene
	scene->addChild(layer);
	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Level5::init()
{
	if (!Level2::init())
	{
		return false;
	}


	cloudScheduler();
	initClouds();
	return true;
}

void Level5::initializeVariables(){
	Level2::initializeVariables();
	CustomAudioManager::getInstance()->stopAll();
	CustomAudioManager::getInstance()->playBackgroundSound("music/Lensko.wav", true);

	for (int i = 0; i < _cloudsPerRow; i++){
		_isPositionFree.push_back(false);
	}
	setTag(5);//level5
	_bg->removeFromParent();
	_bg = new Background("fondo3");
	_bg->setParent(_gameBatchNode, BackgroundPos);
	_bg->setSpeed(100);
	blizz = Blizzard::create();
	addChild(blizz, ForegroundPos);

}

void Level5::initClouds(){
	_numOfClouds = 18;
	_cloudIndex = 0;
	for (int i = 0; i < _numOfClouds; i++){
		auto cloud = Cloud::create();
		cloud->setTarget(_player);
		_clouds.pushBack(cloud);
		_gameBatchNode->addChild(cloud, ForegroundPos);
	}

}

void Level5::cloudScheduler()
{
	//cloud ratio
	DelayTime *delayAction = DelayTime::create(15.0f);
	// perform the selector call
	CallFunc *callSelectorAction = CallFunc::create(CC_CALLBACK_0(Level5::cloudPositioner, this));
	_cloudsScheduler = RepeatForever::create(Sequence::create(callSelectorAction, delayAction, NULL));
	_cloudsScheduler->setTag(CLOUDS_TAG);
	// run the action all the time
	_cloudsScheduler->retain();
	runAction(_cloudsScheduler);

}
void Level5::cloudPositioner()
{
	float spacingBetweenClouds = (20.0f / _cloudsPerRow) * getScaleX();
	auto freeIndex = RandomHelper::random_int(0, 4);
	_isPositionFree.at(freeIndex) = true;
	_isPositionFree.at(freeIndex + 1) = true;
	//cada nube mide 50 * 50
	int positionY = _visibleSize.height + 50 * 0.5;
	//posicion X inicial.
	float positionX = 50 * 0.5;
	for (int i = 0; i < _cloudsPerRow; i++){
		_cloudIndex = _cloudIndex % _numOfClouds;
		if (_isPositionFree.at(i)){
			positionX += 50 + spacingBetweenClouds;
		}
		else if (!_isPositionFree.at(i)){
			_clouds.at(_cloudIndex)->setVisible(true);
			_clouds.at(_cloudIndex)->setPosition(Point(positionX, positionY));
			positionX += 50 + spacingBetweenClouds;
			_cloudIndex++;
		}

	}
	_isPositionFree.at(freeIndex) = false;
	_isPositionFree.at(freeIndex + 1) = false;
}



void Level5::update(float dt)
{
	Level2::update(dt);
	if (!_player->isVisible()){
		stopActionByTag(CLOUDS_TAG);
	}

}

void Level5::respawnButtonAction()
{
	Level2::respawnButtonAction();
	runAction(_cloudsScheduler);
	for (Cloud* cl : _clouds){
		cl->setVisible(false);
	}
}

void Level5::pauseButtonAction()
{
	Level2::pauseButtonAction();
	blizz->pause();
	for (Cloud* cl : _clouds){
		cl->pause();
	}
}

void Level5::playButtonAction()
{
	Level2::playButtonAction();
	blizz->resume();
	for (Cloud* cl : _clouds){
		cl->resume();
	}
}
