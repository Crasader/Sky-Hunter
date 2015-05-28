#ifndef __LEVEL4_SCENE_H__
#define __LEVEL4_SCENE_H__
#include "BaseGameLayer.h"
#include "BasicEnemy.h"

class HealthParticle;

class Level4 : public BaseGameLayer
{

private:
	HealthParticle* _health;


	void awakeEnemy();
	void checkCollisions();
	void awakeEnemyScheduler();
	void initActors();

protected:
	virtual void respawnButtonAction();
	virtual void pauseButtonAction();
	virtual void playButtonAction();

public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void update(float dt);

	CREATE_FUNC(Level4);
};

#endif // __LEVEL4_SCENE_H__