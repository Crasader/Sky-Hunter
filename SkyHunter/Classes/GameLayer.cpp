#include "GameLayer.h"
#include "SimpleAudioEngine.h"
#include "GameManager.h"

using namespace CocosDenshion;

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
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Hunter.plist", "Hunter.png");
	SpriteBatchNode* gameBatchNode = SpriteBatchNode::create("Hunter.png");
	addChild(gameBatchNode);

	//create bg
	_bg = new Background();
	_bg->setParent(gameBatchNode);

	auto h = ParticleSystemQuad::create("impact.plist");
	h->setPosition(_visibleSize.width*0.5, _visibleSize.height*0.5);
	h->setScale(0.1);
	addChild(h);
	
	
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
	createUI();

	//start game loop
	this->schedule(schedule_selector(GameLayer::update));


	//start sound loop
	SimpleAudioEngine::getInstance()->playBackgroundMusic("music/game_loop.mp3", true);
	
	return true;
}


void GameLayer::update(float dt){
	if (_player->isVisible()){
		_bg->update(dt);
	}
	//update ui
	_healthBar->setScaleX(static_cast<float>(_player->getHealth()) / static_cast<float>(MAX_HEALTH));

	_ostr << GameManager::getInstance()->getPlayerScore();

	_scoreDisplay->setString(_ostr.str());
	_ostr.str("");

	if (_scoreDisplay->getBoundingBox().intersectsRect(_scoreLabel->getBoundingBox())){
		_scoreLabel->setPositionX(_scoreDisplay->getPositionX() - _scoreDisplay->getBoundingBox().size.width);
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

void GameLayer::createUI(){
	auto healthContainerIndicator = Sprite::create("health_container_indicartor.png");
	healthContainerIndicator->setAnchorPoint(Point(0, 0.5));
	healthContainerIndicator->setPosition(Point(20, _visibleSize.height - 20));
	addChild(healthContainerIndicator);
	auto nextPosition = Point(healthContainerIndicator->getPositionX() + healthContainerIndicator->getBoundingBox().size.width+5, healthContainerIndicator->getPositionY());

	auto healthContainer = Sprite::create("health_container.png");
	healthContainer->setScaleY(0.80f);
	healthContainer->setAnchorPoint(Point(0, 0.5));
	healthContainer->setPosition(nextPosition);
	addChild(healthContainer);

	_healthBar = Sprite::create("health_bar.png");
	_healthBar->setAnchorPoint(Point(0, 0.5));
	_healthBar->setPosition(nextPosition);
	_healthBar->setScaleY(0.78f);
	_healthBar->setScaleX(1);
	addChild(_healthBar);

	//score dsiplay 
	_scoreDisplay = Label::createWithTTF("0", "fonts/arial.ttf", 15);
	_scoreDisplay->setAnchorPoint(Point(1, 0.5));
	_scoreDisplay->setPosition(Point(_visibleSize.width - 20, _visibleSize.height - 20));
	_scoreDisplay->setTextColor(Color4B::BLACK);
	addChild(_scoreDisplay);

	//score label
	_scoreLabel = Label::createWithTTF("Score: ", "fonts/arial.ttf", 15);
	_scoreLabel->setAnchorPoint(Point(1, 0.5));
	_scoreLabel->setPosition(_scoreDisplay->getPosition());
	_scoreLabel->setPositionX(_scoreDisplay->getPositionX() - _scoreDisplay->getBoundingBox().size.width);
	_scoreLabel->setTextColor(Color4B::BLACK);
	addChild(_scoreLabel);
}

void GameLayer::checkCollisions(){
	for (int i = 0; i < _numEnemies; i++){
		auto enemy = _enemyPool.at(i);
		if (_player->getBoundingBox().intersectsRect(enemy->getBoundingBox())
			&& enemy->isVisible() && _player->isVisible()){
			enemy->setCurrentAnimation(BasicEnemy::Animations::EXPLOSION);
			_player->setHealth(0);
		}
	}
}

