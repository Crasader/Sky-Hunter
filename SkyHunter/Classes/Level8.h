#ifndef __LEVEL8_SCENE_H__
#define __LEVEL8_SCENE_H__
#include "BaseGameLayer.h"
#include "BasicEnemy.h"

class HealthParticle;

class Level8 : public BaseGameLayer
{

private:
	HealthParticle* _health;
	int _numEnemies;
	int _enemyIndex;
	cocos2d::Vector<BasicEnemy*> _enemyPool;
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

	CREATE_FUNC(Level8);
};

#endif // __LEVEL8_SCENE_H__