#include "Level1.h"
#include "CustomAudioManager.h"
#include "GameManager.h"
#include "MainMenuLayer.h"

USING_NS_CC;
using namespace Levels;
using namespace Actors;
using namespace Menus;


Scene* Level1::createScene()
{
	auto scene = Scene::create();
	auto layer = Level1::create();
	scene->addChild(layer);
	return scene;
}

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

	_bg = new Components::Background("fondo");
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
		auto enemy = Actors::BasicEnemy::create();
		//da informacion a los enemigos acerca del player
		enemy->setTarget(_player);
		_enemyPool.pushBack(enemy);
		_gameBatchNode->addChild(enemy, ForegroundPos);
	}
	//da info al player aerca de los enemigos
	_player->setTargets(_enemyPool);

}




void Level1::update(float dt)
{
	BaseGameLayer::update(dt);
	_player->update(dt);
	//colisiones entre enemigos y player
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

	auto enemy = _enemyPool.at(_enemyIndex);
	//posicionamos de forma aleatoria en el eje x un enemigo, teniendo en cuenta
	//que cada enemigo mide 50*50
	enemy->setPositionX(RandomHelper::random_int(static_cast<int>(0 + 50 * 0.5),
		static_cast<int>(_visibleSize.width - 50 * 0.5)));
	enemy->setPositionY(_visibleSize.height + 50 * 0.5);
	enemy->setCurrentAnimation(Actors::BasicEnemy::Animations::IDLE);
	//reseteamos el estado del enemigo
	if (!enemy->isVisible()){
		enemy->setVisible(true);
	}
	_enemyIndex++;
}


void Level1::awakeEnemyScheduler()
{
	//se generera un enemigo cada _awakeSpeed
	DelayTime *delayAction = DelayTime::create(_awakeSpeed);
	// creamos la acción que despertara a los enemigos
	CallFunc *callSelectorAction = CallFunc::create(CC_CALLBACK_0(Level1::awakeEnemy, this));
	auto awakeEnemySequence = Sequence::create(delayAction, callSelectorAction, NULL);
	// repetimos esto hasta el final del juego
	runAction(RepeatForever::create(awakeEnemySequence));
}


void Level1::checkCollisions()
{
	for (int i = 0; i < _numEnemies; i++){
		auto enemy = _enemyPool.at(i);
		if (_player->getBoundingBox().intersectsRect(enemy->getBoundingBox())
			&& enemy->isVisible() && _player->isVisible()){
			enemy->setCurrentAnimation(Actors::BasicEnemy::Animations::EXPLOSION);
			_player->setHealth(0);
		}
	}
}

