#include "Level4.h"
#include "CustomAudioManager.h"
#include "GameManager.h"
#include "MainMenuLayer.h"
#include "Blizzard.h"

USING_NS_CC;

Scene* Level4::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	// 'layer' is an autorelease object
	auto layer = Level4::create();
	// add layer as a child to scene
	scene->addChild(layer);
	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Level4::init()
{
	if (!BaseGameLayer::init())
	{
		return false;
	}

	initializeVariables();
	initActors();
	scheduleActions();
	initClouds();
	return true;
}

void Level4::initializeVariables(){
	CustomAudioManager::getInstance()->playBackgroundSound("music/Lensko.wav", true);
	_numEnemies = 20;
	for (int i = 0; i < _cloudsPerRow; i++){
		_isPositionFree.push_back(false);
	}
	setTag(4);//level4

	_scoreToCompleTheLevel = 700;

	_bg = new Background("fondo3");
	_bg->setParent(_gameBatchNode, BackgroundPos);
	_bg->setSpeed(100);
	blizz = Blizzard::create();
	addChild(blizz,ForegroundPos);
	
}

void Level4::initClouds(){
	_numOfClouds = 18;
	_cloudIndex = 0;
	for (int i = 0; i < _numOfClouds; i++){
		auto cloud = Cloud::create();
		cloud->setTarget(_player);
		_clouds.pushBack(cloud);
		_gameBatchNode->addChild(cloud, ForegroundPos);
	}

}

void Level4::cloudScheduler()
{
	//cloud ratio
	DelayTime *delayAction = DelayTime::create(10.0f);
	// perform the selector call
	CallFunc *callSelectorAction = CallFunc::create(CC_CALLBACK_0(Level4::cloudPositioner, this));
	_cloudsScheduler = RepeatForever::create(Sequence::create(callSelectorAction, delayAction, NULL));
	_cloudsScheduler->setTag(CLOUDS_TAG);
	// run the action all the time
	runAction(_cloudsScheduler);

}
void Level4::cloudPositioner()
{

	float spacingBetweenClouds = (20.0f / _cloudsPerRow) * getScaleX();
	auto freeIndex = RandomHelper::random_int(0,4);
	_isPositionFree.at(freeIndex) = true;
	_isPositionFree.at(freeIndex+1) = true;
	//cada nube mide 50 + 50
	int positionY = _visibleSize.height + 50 * 0.5;
	//posicion X inicial.
	float positionX = 50*0.5;
	for (int i = 0; i < _cloudsPerRow; i++){
		_cloudIndex = _cloudIndex % _numOfClouds;
		if (_isPositionFree.at(i)){
			positionX += 50 + spacingBetweenClouds;
		}else if (!_isPositionFree.at(i)){
			_clouds.at(_cloudIndex)->setVisible(true);
			_clouds.at(_cloudIndex)->setPosition(Point(positionX, positionY));
			positionX += 50 + spacingBetweenClouds;
			_cloudIndex++;
		}

	}
	_isPositionFree.at(freeIndex) = false;
	_isPositionFree.at(freeIndex + 1) = false;
}



void Level4::scheduleActions(){
	awakeEnemyScheduler();
	cloudScheduler();
	//comienza el bucle del juego
	this->schedule(schedule_selector(Level4::update));
}

void Level4::initActors()
{
	for (int i = 0; i < _numEnemies; i++){
		auto enemy = BasicEnemy::create();
		//tell the enemies about the player.
		enemy->setTarget(_player);
		_enemyPool.pushBack(enemy);
		_gameBatchNode->addChild(enemy, ForegroundPos);
	}
	_player->setTargets(_enemyPool);
}




void Level4::update(float dt)
{
	BaseGameLayer::update(dt);
	_player->update(dt);
	if (!_player->isVisible()){
		stopActionByTag(CLOUDS_TAG);
	}
	//check for collision between enemies & player
	checkCollisions();
}

void Level4::respawnButtonAction()
{
	BaseGameLayer::respawnButtonAction();
	stopAllActions();
	scheduleActions();

	for (int i = 0; i < _numEnemies; i++){
		_enemyPool.at(i)->reset();
	}
	for (Cloud* cl : _clouds){
		cl->setVisible(false);
	}
}

void Level4::pauseButtonAction()
{
	BaseGameLayer::pauseButtonAction();

	
	blizz->pause();
	_player->pause();
	for (Sprite* enemy : _enemyPool){
		enemy->pause();
	}
	for (Cloud* cl : _clouds){
		cl->pause();
	}
}

void Level4::playButtonAction()
{
	BaseGameLayer::playButtonAction();

	blizz->resume();
	_player->resume();
	for (Sprite* enemy : _enemyPool){
		enemy->resume();
	}
	for (Cloud* cl : _clouds){
		cl->resume();
	}
}

void Level4::awakeEnemy()
{
	_enemyIndex = _enemyIndex % _numEnemies;
	//select enemy
	auto enemy = _enemyPool.at(_enemyIndex);
	//Positioning
	//the enemy size is 50*50, take care about the anchor point.
	enemy->setPositionX(RandomHelper::random_int(static_cast<int>(0 + 50 * 0.5),
		static_cast<int>(_visibleSize.width - 50 * 0.5)));
	enemy->setPositionY(_visibleSize.height + 50 * 0.5);
	enemy->setCurrentAnimation(BasicEnemy::Animations::IDLE);
	//awake after positioning
	if (!enemy->isVisible()){
		enemy->setVisible(true);
	}
	_enemyIndex++;
}


void Level4::awakeEnemyScheduler()
{
	//enemy ratio
	// set up the time delay
	DelayTime *delayAction = DelayTime::create(1.5f);
	// perform the selector call
	CallFunc *callSelectorAction = CallFunc::create(CC_CALLBACK_0(Level4::awakeEnemy, this));
	auto awakeEnemySequence = Sequence::create(delayAction, callSelectorAction, NULL);
	// run the action all the time
	runAction(RepeatForever::create(awakeEnemySequence));
}


void Level4::checkCollisions()
{
	for (int i = 0; i < _numEnemies; i++){
		auto enemy = _enemyPool.at(i);
		if (_player->getBoundingBox().intersectsRect(enemy->getBoundingBox())
			&& enemy->isVisible() && _player->isVisible()){
			enemy->setCurrentAnimation(BasicEnemy::Animations::EXPLOSION);
			_player->setHealth(0);
		}
	}
}