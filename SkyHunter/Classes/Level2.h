#ifndef __LEVEL2_SCENE_H__
#define __LEVEL2_SCENE_H__
#include "BaseGameLayer.h"

namespace Components{
	class HealthParticle;
	class PlayerUpgradeParticle;
}
namespace Levels{
	class Level2 : public BaseGameLayer
	{

	private:
		enum ActionScheduler { BasicScheduler, MediumScheduler };
		Components::HealthParticle* _health;
		Components::PlayerUpgradeParticle * _upgrade;
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
		void launchHealth();
		void launchUpgrade();
		void launchMediumEnemies();
		void schduleUpgrades();

	protected:
		virtual void initializeVariables();
		virtual void respawnButtonAction();
		virtual void pauseButtonAction();
		virtual void playButtonAction();

	public:
		CC_SYNTHESIZE(float, _basicAwakeSpeed, BasicAwakeSpeed);
		CC_SYNTHESIZE(float, _mediumAwakeSpeed, MediumAwakeSpeed);
		static cocos2d::Scene* createScene();
		virtual bool init();
		void update(float dt);

		CREATE_FUNC(Level2);
	};
}
#endif // __LEVEL2_SCENE_H__