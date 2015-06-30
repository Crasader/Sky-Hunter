#ifndef __BACKGROUND3PARTS_H__
#define __BACKGROUND3PARTS_H__

#include "cocos2d.h"
namespace Components{
	class BackGround3Parts
	{

	private:
		bool _initialiced;
		cocos2d::Size _screen;
		cocos2d::Sprite* _bgPart1;
		cocos2d::Sprite* _bgPart2;
		cocos2d::Sprite* _bgPart3;
		cocos2d::Sprite* _bgPart4;
		cocos2d::Sprite* _bgPart5;


	public:
		virtual void setParent(cocos2d::Node* parent);
		void update(float dt);
		BackGround3Parts();
		~BackGround3Parts();

		CC_SYNTHESIZE(float, _speed, Speed);
	};
}

#endif //__BACKGROUND3PARTS_H__