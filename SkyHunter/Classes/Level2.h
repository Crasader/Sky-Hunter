#ifndef __LEVEL2_SCENE_H__
#define __LEVEL2_SCENE_H__
#include "BaseGameLayer.h"


class HealthParticle;
class PlayerUpgradeParticle;

class Level2 : public BaseGameLayer
{

private:
	enum ActionScheduler { BasicScheduler, MediumScheduler };
	HealthParticle* _health;
	PlayerUpgradeParticle * _upgrade;
	bool _mediumSchedulerRunning;

	//enemigos de nivel medio
	int _numMediumEnemies;
	int _mediumEnemyIndex;

	void awakeBasicEnemy();
	void awakeMediumEnemy();
	void checkCollisions();
	void awakeBasicEnemyScheduler();
	void awakeMediumEnemyScheduler();
	void initActors();
	void scheduleActions();
	void initializeVariables();
	void launchHealth();
	void launchUpgrade();
	void launchMediumEnemies();
	void schduleUpgrades();

protected:
	virtual void respawnButtonAction();
	virtual void pauseButtonAction();
	virtual void playButtonAction();

public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void update(float dt);

	CREATE_FUNC(Level2);
};

#endif // __LEVEL2_SCENE_H__