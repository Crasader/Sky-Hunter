#ifndef __LEVEL4_SCENE_H__
#define __LEVEL4_SCENE_H__

#include "BaseGameLayer.h"
#include "Cloud.h"

class HealthParticle;
class Blizzard;


class Level4 : public BaseGameLayer
{

private:
	Blizzard* blizz;
	int CLOUDS_TAG = 0;
	cocos2d::Action* _cloudsScheduler;
	const int _cloudsPerRow = 6;
	int _numOfClouds;
	int _cloudIndex;

	cocos2d::Vector<Cloud* > _clouds;
	std::vector<bool> _isPositionFree;

	void checkCollisions();
	void scheduleActions();

	void initActors();
	void initClouds();

	void cloudScheduler();
	void cloudPositioner();

	void awakeEnemyScheduler();
	void awakeEnemy();

protected:
	virtual void initializeVariables();
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