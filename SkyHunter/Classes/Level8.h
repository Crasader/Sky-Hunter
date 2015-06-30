#ifndef __LEVEL8_SCENE_H__
#define __LEVEL8_SCENE_H__

#include "Level2.h"
namespace Levels{

	class Level8 : public Level2
	{
	protected:
		virtual void initializeVariables();

	public:
		static cocos2d::Scene* createScene();
		virtual bool init();

		CREATE_FUNC(Level8);
	};
}

#endif // __LEVEL8_SCENE_H__