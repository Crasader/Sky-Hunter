#include "Level1.h"
#include "CustomAudioManager.h"
#include "GameManager.h"
#include "MainMenuLayer.h"

USING_NS_CC;

Scene* Level1::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	// 'layer' is an autorelease object
	auto layer = Level1::create();
	// add layer as a child to scene
	scene->addChild(layer);
	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Level1::init()
{
	if (!BaseGameLayer::init())
	{
		return false;
	}

	initializeVariables();
	initActors();
	scheduleActions();
	return true;
}

void Level1::initializeVariables(){
	_numEnemies = 20;
	_awakeSpeed = 1.0f;
	setTag(1);//level1
	//lanza el bucle de sonido
	CustomAudioManager::getInstance()->playBackgroundSound("music/Cetus.wav", true);
	_scoreToCompleTheLevel = 750;

	_bg = new Background("fondo");
	_bg->setParent(_gameBatchNode, BackgroundPos);
}

void Level1::scheduleActions(){
	awakeEnemyScheduler();

	//comienza el bucle del juego
	this->schedule(schedule_selector(Level1::update));


}

void Level1::initActors()
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




void Level1::update(float dt)
{
	BaseGameLayer::update(dt);
	_player->update(dt);
	//check for collision between enemies & player
	checkCollisions();
}

void Level1::respawnButtonAction()
{
	BaseGameLayer::respawnButtonAction();
	for (int i = 0; i < _numEnemies; i++){
		_enemyPool.at(i)->reset();
	}
}

void Level1::pauseButtonAction()
{
	BaseGameLayer::pauseButtonAction();
	_player->pause();
	for (Sprite* enemy : _enemyPool){
		enemy->pause();
	}
}

void Level1::playButtonAction()
{
	BaseGameLayer::playButtonAction();
	_player->resume();
	for (Sprite* enemy : _enemyPool){
		enemy->resume();
	}
}

void Level1::awakeEnemy()
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


void Level1::awakeEnemyScheduler()
{
	//enemy ratio
	// set up the time delay
	DelayTime *delayAction = DelayTime::create(_awakeSpeed);
	// perform the selector call
	CallFunc *callSelectorAction = CallFunc::create(CC_CALLBACK_0(Level1::awakeEnemy, this));
	auto awakeEnemySequence = Sequence::create(delayAction, callSelectorAction, NULL);
	// run the action all the time
	runAction(RepeatForever::create(awakeEnemySequence));
}


void Level1::checkCollisions()
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

