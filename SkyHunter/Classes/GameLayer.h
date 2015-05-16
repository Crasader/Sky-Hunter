#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Background.h"
#include "BasicEnemy.h"
#include "Player.h"

class GameLayer : public cocos2d::Layer
{

private:

	std::ostringstream _ostr;
	int _numEnemies;
	int _enemyIndex;
	cocos2d::Sprite* _healthBar;
	cocos2d::Size _visibleSize;
	cocos2d::Label* _scoreDisplay;
	cocos2d::Label* _scoreLabel;

	Background* _bg;
	Player* _player;
	cocos2d::Vector<BasicEnemy*> _enemyPool;

	void awakeEnemy();

	void checkCollisions();

	void createUI();

public:
	~GameLayer();
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	void update(float dt);

    
    // implement the "static create()" method manually
	CREATE_FUNC(GameLayer);
};

#endif // __HELLOWORLD_SCENE_H__
