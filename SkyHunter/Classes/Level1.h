#ifndef __LEVEL1_SCENE_H__
#define __LEVEL1_SCENE_H__

#include "BaseGameLayer.h"


class Level1 : public BaseGameLayer
{

private:
	void awakeEnemy();
	void checkCollisions();
	void awakeEnemyScheduler();
	void initActors();
	void scheduleActions();
	

protected:
	virtual void initializeVariables();
	virtual void respawnButtonAction();
	virtual void pauseButtonAction();
	virtual void playButtonAction();

public:
	CC_SYNTHESIZE(float, _awakeSpeed, AwakeSpeed);
    static cocos2d::Scene* createScene();
    virtual bool init();
	void update(float dt);

	CREATE_FUNC(Level1);
};

#endif // __LEVEL1_SCENE_H__
