#ifndef __LEVEL9_SCENE_H__
#define __LEVEL9_SCENE_H__

#include "Level3.h"


namespace Levels{
	class Level9 : public Level3
	{
	protected:
		virtual void initializeVariables();

	public:
		static cocos2d::Scene* createScene();
		virtual bool init();
		CREATE_FUNC(Level9);
	};
}

#endif // __LEVEL1_SCENE_H__