#ifndef __BASEGAMELAYER_H__
#define __BASEGAMELAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Player.h"
#include "Background.h"

class BaseGameLayer : public cocos2d::Layer
{
private:
	int _completionPercentage;
	bool isLevelComplete;
	std::ostringstream _ostr;
	cocos2d::ui::Button* _pauseButton;
	cocos2d::ui::Button* _respawnButton;
	cocos2d::ui::Button* _playAgainButton;
	cocos2d::ui::Button* _playButton;
	cocos2d::ui::Button* _backButton;
	cocos2d::Sprite* _healthBar;
	cocos2d::Label* _scoreLabel;
	cocos2d::Label* _completionPercentageLabel;
	void createHealthIndicator();
	void createScoreAndPercentageLabels();
	void createPauseAndResumeButtons();
	void createRespawnButton();
	void levelCompleteActions();
	void levelCompleteActionsHelper();

protected:
	enum RenderOrder { BackgroundPos, ForegroundPos, UIPos };
	//enemigos totales
	int _numEnemies;
	int _enemyIndex;
	//pool total de enemigos
	cocos2d::Vector<BasicEnemy*> _enemyPool;

	Player* _player;

	Background* _bg;
	int _scoreToCompleTheLevel;
	cocos2d::Size _visibleSize;
	cocos2d::SpriteBatchNode* _gameBatchNode;

	virtual void resetPlayer();
	virtual void respawnButtonAction();
	virtual void pauseButtonAction();
	virtual void playButtonAction();
	virtual void actionButtonBack();
	
public:
	virtual ~BaseGameLayer();
	virtual void update(float dt);
	virtual bool init();

	static cocos2d::Scene* createScene();

	CREATE_FUNC(BaseGameLayer);
};

#endif //__BASEGAMELAYER_H__

