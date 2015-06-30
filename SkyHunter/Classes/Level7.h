#ifndef __LEVEL7_SCENE_H__
#define __LEVEL7_SCENE_H__

#include "Level1.h"


namespace Levels{
	class Level7 : public Level1
	{

	protected:
		virtual void initializeVariables();

	public:
		static cocos2d::Scene* createScene();
		virtual bool init();
		CREATE_FUNC(Level7);
	};
}

#endif // __LEVEL7_SCENE_H__