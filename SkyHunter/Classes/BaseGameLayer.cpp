#include "BaseGameLayer.h"
#include "GameManager.h"
#include "MainMenuLayer.h"
#include "SelectMenuLayer.h"
#include "AudioEngine.h"

USING_NS_CC;

BaseGameLayer::~BaseGameLayer(){
	CC_SAFE_DELETE(_bg);
}

Scene* BaseGameLayer::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	// 'layer' is an autorelease object
	auto layer = BaseGameLayer::create();
	// add layer as a child to scene
	scene->addChild(layer);
	// return the scene
	return scene;
}


bool BaseGameLayer::init(){
	if (!Layer::init()){
		return false;
	}
	_visibleSize = Director::getInstance()->getVisibleSize();
	_completionPercentage = 0;
	_scoreToCompleTheLevel = 1000;
	isLevelComplete = false;
	setTag(0);
	GameManager::getInstance()->setPlayerScore(0);

	//todas las pantallass de nuestro juego usaran este sprite sheet
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Hunter.plist", "Hunter.png");
	_gameBatchNode = SpriteBatchNode::create("Hunter.png");
	addChild(_gameBatchNode);

	_bg = new Background();
	_bg->setParent(_gameBatchNode, BackgroundPos);


	_player = Player::create();
	_player->setPosition(_visibleSize.width*0.5, _visibleSize.height*0.3);
	_gameBatchNode->addChild(_player, ForegroundPos);

	createHealthIndicator();
	createScoreAndPercentageLabels();
	createPauseAndResumeButtons();
	createRespawnButton();

	//crete back button
	_backButton = ui::Button::create("back0", "back1", "back1", ui::Widget::TextureResType::PLIST);
	_backButton->setAnchorPoint(Point(0, 0.5));
	_backButton->addClickEventListener(CC_CALLBACK_0(BaseGameLayer::actionButtonBack, this));
	_backButton->setPosition(Point(42.5* getScaleX(), 50 * getScaleY()));
	_backButton->setEnabled(false);
	_backButton->setVisible(false);
	addChild(_backButton);

	//win label


	return true;
}

void BaseGameLayer::levelCompleteActions(){
	if (!isLevelComplete){
		float aniTime = 2.0f;
		auto winnerLabel = Label::createWithTTF("Level complete", "fonts/arial.ttf", 40);
		winnerLabel->setTextColor(Color4B::ORANGE);
		winnerLabel->setPosition(Point(_visibleSize.width*0.5, _visibleSize.height - 100 * getScaleY()));
		addChild(winnerLabel, UIPos);
		GameManager::getInstance()->saveGame(getTag());
		
		auto moveTo = MoveTo::create(aniTime, Point(_visibleSize.width*0.5, _visibleSize.height *0.5));
		winnerLabel->runAction(moveTo);

		CallFunc *loadMenu = CallFunc::create(CC_CALLBACK_0(BaseGameLayer::levelCompleteActionsHelper, this));
		DelayTime *delayAction = DelayTime::create(aniTime);
		auto sequence = Sequence::create(delayAction, loadMenu, NULL);
		runAction(sequence);
	}
	isLevelComplete = true;
}

void BaseGameLayer::levelCompleteActionsHelper(){
	experimental::AudioEngine::stopAll();
	Director::getInstance()->replaceScene(SelectMenuLayer::createScene());
}


void BaseGameLayer::resetPlayer(){
	_player->reset();
	_player->setPosition(_visibleSize.width*0.5, _visibleSize.height*0.3);
	GameManager::getInstance()->setPlayerScore(0);
}


void BaseGameLayer::createHealthIndicator(){
	auto healthContainerIndicator = Sprite::createWithSpriteFrameName("health_container_indicartor");
	healthContainerIndicator->setAnchorPoint(Point(0, 0.5));
	healthContainerIndicator->setPosition(Point(20 * getScaleX(), _visibleSize.height - 20 + getScaleY()));
	_gameBatchNode->addChild(healthContainerIndicator, UIPos);
	auto nextPosition = Point(healthContainerIndicator->getPositionX() + healthContainerIndicator->getBoundingBox().size.width + 5, healthContainerIndicator->getPositionY());

	auto healthContainer = Sprite::createWithSpriteFrameName("health_container");
	healthContainer->setScaleY(0.80f);
	healthContainer->setAnchorPoint(Point(0, 0.5));
	healthContainer->setPosition(nextPosition);
	_gameBatchNode->addChild(healthContainer, UIPos);

	_healthBar = Sprite::createWithSpriteFrameName("health_bar");
	_healthBar->setAnchorPoint(Point(0, 0.5));
	_healthBar->setPosition(nextPosition);
	_healthBar->setScaleY(0.78f);
	_healthBar->setScaleX(1);
	_gameBatchNode->addChild(_healthBar, UIPos);
}

void BaseGameLayer::createScoreAndPercentageLabels(){
	//score
	_scoreLabel = Label::createWithTTF("Score: 0", "fonts/arial.ttf", 15);
	_scoreLabel->setAnchorPoint(Point(0.5, 0.5));
	_scoreLabel->setPosition(Point(_visibleSize.width*0.5, _visibleSize.height - 20 * getScaleY()));
	_scoreLabel->setTextColor(Color4B::BLACK);
	addChild(_scoreLabel, UIPos);

	//percentage
	_completionPercentageLabel = Label::createWithTTF("0 %", "fonts/arial.ttf", 30);
	_completionPercentageLabel->setAnchorPoint(Point(1, 0));
	_completionPercentageLabel->setTextColor(Color4B::ORANGE);
	_completionPercentageLabel->setPosition(Point(_visibleSize.width - 5* getScaleX(), 5 * getScaleY()));
	addChild(_completionPercentageLabel);
}

void BaseGameLayer::createPauseAndResumeButtons(){
	//pause button
	_pauseButton = ui::Button::create("pause0", "pause1", "pause1", ui::Widget::TextureResType::PLIST);
	_pauseButton->setScale(0.7f);
	_pauseButton->addClickEventListener(CC_CALLBACK_0(BaseGameLayer::pauseButtonAction, this));
	_pauseButton->setAnchorPoint(Point(1, 0.5));
	_pauseButton->setPosition(Point(_visibleSize.width - 20 * getScaleX(), _visibleSize.height - 20 + getScaleY()));
	addChild(_pauseButton, UIPos);

	//play
	_playButton = ui::Button::create("play0", "play1", "play1", ui::Widget::TextureResType::PLIST);
	_playButton->setScale(0.7f);
	_playButton->addClickEventListener(CC_CALLBACK_0(BaseGameLayer::playButtonAction, this));
	_playButton->setAnchorPoint(Point(1, 0.5));
	_playButton->setVisible(false);
	_playButton->setEnabled(false);
	_playButton->setPosition(_pauseButton->getPosition());
	addChild(_playButton, UIPos);
}

void BaseGameLayer::createRespawnButton()
{
	_respawnButton = ui::Button::create("respawn0", "respawn1", "respawn1", ui::Widget::TextureResType::PLIST);
	_respawnButton->setPosition(Point(_visibleSize.width*0.5, _visibleSize.height*0.5));
	_respawnButton->setVisible(false);
	_respawnButton->setEnabled(false);
	_respawnButton->addClickEventListener(CC_CALLBACK_0(BaseGameLayer::respawnButtonAction, this));
	addChild(_respawnButton, UIPos);
}

void BaseGameLayer::actionButtonBack()
{
	experimental::AudioEngine::stopAll();
	Director::getInstance()->replaceScene(TransitionSplitRows::create(1, MainMenuLayer::createScene()));
}

void BaseGameLayer::update(float dt)
{
	if (_player->isVisible()){
		_bg->update(dt);
	}
	else{
		_respawnButton->setVisible(true);
		_respawnButton->setEnabled(true);
		_backButton->setEnabled(true);
		_backButton->setVisible(true);
	}

	//update ui
	_healthBar->setScaleX(static_cast<float>(_player->getHealth()) / static_cast<float>(MAX_HEALTH));
	_ostr << GameManager::getInstance()->getPlayerScore();
	_scoreLabel->setString("Score: " + _ostr.str());
	_ostr.str("");
	_ostr << (GameManager::getInstance()->getPlayerScore() * 100) / _scoreToCompleTheLevel;
	_completionPercentageLabel->setString( _ostr.str() + " %");
	_ostr.str("");
	if (GameManager::getInstance()->getPlayerScore() >= _scoreToCompleTheLevel){
		levelCompleteActions();
	}
}

void BaseGameLayer::pauseButtonAction()
{
	pause();
	_pauseButton->setVisible(false);
	_pauseButton->setEnabled(false);
	_playButton->setVisible(true);
	_playButton->setEnabled(true);
	_respawnButton->setVisible(true);
	_respawnButton->setEnabled(true);
	_backButton->setEnabled(true);
	_backButton->setVisible(true);
}

void BaseGameLayer::playButtonAction()
{
	resume();
	_pauseButton->setVisible(true);
	_pauseButton->setEnabled(true);
	_playButton->setVisible(false);
	_playButton->setEnabled(false);
	_respawnButton->setVisible(false);
	_respawnButton->setEnabled(false);
	_backButton->setEnabled(false);
	_backButton->setVisible(false);
}

void BaseGameLayer::respawnButtonAction()
{
	playButtonAction();
	resetPlayer();
	_respawnButton->setVisible(false);
	_respawnButton->setEnabled(false);
}
