
#ifndef __SELECTMENULAYER_H__
#define __SELECTMENULAYER_H__

#define NUM_LEVELS 9

#include "MainMenuLayer.h"
#include "ui/CocosGUI.h"

namespace Menus{
	class SelectMenuLayer : public MainMenuLayer
	{
	private:
		std::ostringstream _ostr;
		void actionButtonBack();
		void initButtons(cocos2d::Vector<cocos2d::ui::Button*>& vector, std::vector<std::function<void(Ref*)>>& functions);

	public:
		virtual bool init();
		static cocos2d::Scene* createScene();
		// implement the "static create()" method manually
		CREATE_FUNC(SelectMenuLayer);
	};
}

#endif //__MAINMENULAYER_H__