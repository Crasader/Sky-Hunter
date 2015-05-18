#ifndef __BASEGAMELAYER_H__
#define __BASEGAMELAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Player.h"
#include "Background.h"

class BaseGameLayer : public cocos2d::Layer
{
private:
	std::ostringstream _ostr;
	cocos2d::ui::Button* _pauseButton;
	cocos2d::ui::Button* _respawnButton;
	cocos2d::ui::Button* _playAgainButton;
	cocos2d::ui::Button* _playButton;
	cocos2d::ui::Button* _backButton;
	cocos2d::Sprite* _healthBar;
	cocos2d::Label* _scoreLabel;
	void createHealthIndicator();
	void createScoreLabel();
	void createPauseAndResumeButtons();
	void createRespawnButton();
	
	

protected:
	enum Order { BackgroundPos, ForegroundPos, UIPos };
	Player* _player;
	Background* _bg;
	cocos2d::Size _visibleSize;
	cocos2d::SpriteBatchNode* _gameBatchNode;

	virtual void resetPlayer();
	virtual void respawnButtonAction();
	virtual void pauseButtonAction();
	virtual void playButtonAction();
	virtual void actionButtonBack();
	
public:
	cocos2d::SpriteBatchNode* getSpriteBatchNode(){ return _gameBatchNode; }
	virtual ~BaseGameLayer();
	virtual void update(float dt);
	virtual bool init();

	static cocos2d::Scene* createScene();

	CREATE_FUNC(BaseGameLayer);
};

#endif

