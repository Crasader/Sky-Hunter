#ifndef __TOUCHCONTROLLER_H__
#define __TOUCHCONTROLLER_H__
#include "cocos2d.h"
namespace Actors{
	class TouchController : public cocos2d::Sprite
	{
	private:
		struct  Controller {
			bool left;
			bool right;
			bool up;
			bool upLeft;
			bool upRight;
			bool down;
			bool downLeft;
			bool downRight;
		};

		cocos2d::Point _tap;
		Controller _controller;
		void resetTouchController();

	public:
		virtual bool init();
		CREATE_FUNC(TouchController);
		void update(float dt);
		Controller getController(){ return _controller; }

	protected:
		//touch call back
		virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
		virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
		virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	};
}
#endif //__TOUCHCONTROLLER_H__

