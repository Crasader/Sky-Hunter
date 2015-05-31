#ifndef __LEVEL5_SCENE_H__
#define __LEVEL5_SCENE_H__

#include "Level2.h"
#include "Cloud.h"

class HealthParticle;
class Blizzard;

class Level5 : public Level2
{
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

	void initClouds();

	void cloudScheduler();
	void cloudPositioner();
protected:
	virtual void initializeVariables();
	virtual void respawnButtonAction();
	virtual void pauseButtonAction();
	virtual void playButtonAction();

public:
	~Level5();
	static cocos2d::Scene* createScene();
	virtual bool init();
	void update(float dt);

	CREATE_FUNC(Level5);
};

#endif // __LEVEL5_SCENE_H__