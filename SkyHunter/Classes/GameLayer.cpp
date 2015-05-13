#include "GameLayer.h"


USING_NS_CC;

GameLayer::~GameLayer(){
	delete _bg;
}

Scene* GameLayer::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	_numEnemies = 20;
	_enemyIndex = 0;


	_visibleSize = Director::getInstance()->getVisibleSize();

	//create node with texture info & init TextureCache
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Hunter.plist");
	SpriteBatchNode* gameBatchNode = SpriteBatchNode::create("Hunter.png");
	addChild(gameBatchNode);

	//create bg
	_bg = new Background();
	_bg->setParent(gameBatchNode);
	
	
	//create player
	_player = Player::create();
	_player->setPosition(_visibleSize.width*0.5, _visibleSize.height*0.3);
	gameBatchNode->addChild(_player);


	for (int i = 0; i < _numEnemies; i++){
		auto enemy = BasicEnemy::create();
		//tell the enemies about the player.
		enemy->setTarget(_player);
		enemy->setVisible(false);
		_enemyPool.pushBack(enemy);
		gameBatchNode->addChild(enemy);
	}

	//tell the player about the enemies
	_player->setTargets(_enemyPool);

	//enemy ratio
	// set up the time delay
	DelayTime *delayAction = DelayTime::create(1.0f);

	// perform the selector call
	CallFunc *callSelectorAction = CallFunc::create(CC_CALLBACK_0(GameLayer::awakeEnemy, this));
	auto awakeEnemySequence = Sequence::create(delayAction, callSelectorAction, NULL);

	// run the action all the time
	runAction(RepeatForever::create(awakeEnemySequence));


	//start game loop
	this->schedule(schedule_selector(GameLayer::update));
	return true;
}


void GameLayer::update(float dt){
	if (_player->isVisible()){
		_bg->update(dt);
	}
	
	_player->update(dt);
	//check for collision between enemies & player
	checkCollisions();
}

void GameLayer::awakeEnemy(){
	_enemyIndex = _enemyIndex % _numEnemies;
	auto enemy = _enemyPool.at(_enemyIndex);
	//Positioning
	//the enemy size is 50+50, take care about the anchor point.
	enemy->setPositionX(RandomHelper::random_int(static_cast<int>(0 + 50 * 0.5),
		static_cast<int>(_visibleSize.width - 50 * 0.5)));
	enemy->setPositionY(_visibleSize.height + 50 * 0.5);
	enemy->setCurrentAnimation(BasicEnemy::Animations::IDLE);

	if (!enemy->isVisible()){
		enemy->setVisible(true);
	}
	_enemyIndex++;
}

void GameLayer::checkCollisions(){
	for (int i = 0; i < _numEnemies; i++){
		auto enemy = _enemyPool.at(i);
		if (_player->getBoundingBox().intersectsRect(enemy->getBoundingBox())
			&& enemy->isVisible() && _player->isVisible()){
			enemy->setCurrentAnimation(BasicEnemy::Animations::EXPLOSION);
			_player->setCurrentAnimation(Player::Animations::EXPLOSION);
		}
	}
}

