#ifndef __LEVEL6_SCENE_H__
#define __LEVEL6_SCENE_H__

#include "Level3.h"
#include "Cloud.h"

namespace Components{
	class Blizzard;
}
namespace Levels{
	class Level6 : public Level3
	{
		Components::Blizzard* blizz;
		int CLOUDS_TAG = 0;
		cocos2d::Action* _cloudsScheduler;
		const int _cloudsPerRow = 6;
		int _numOfClouds;
		int _cloudIndex;

		cocos2d::Vector<Components::Cloud* > _clouds;
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
		~Level6();
		static cocos2d::Scene* createScene();
		virtual bool init();
		void update(float dt);

		CREATE_FUNC(Level6);
	};
}

#endif // __LEVEL6_SCENE_H__