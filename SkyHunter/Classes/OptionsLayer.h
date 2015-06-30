
#ifndef __OPTIONSLAYER_H__
#define __OPTIONSLAYER_H__

#define NUM_LEVELS 9

#include "BaseMenuLayer.h"
#include "ui/CocosGUI.h"

namespace Menus{

	class OptionsLayer : public BaseMenuLayer
	{
	private:
		std::ostringstream _ostr;
		cocos2d::ui::Slider* _effectsVolume;
		cocos2d::ui::Slider* _backGroundVolume;
		cocos2d::Label* _backGroundVolumeLabel;
		cocos2d::Label * _effectsVolumeLabel;
		void actionButtonBack();
		void actionBackGroundVolumeSlider();
		void actionEffectsVolumeSlider();

	public:
		virtual bool init();
		static cocos2d::Scene* createScene();
		// implement the "static create()" method manually
		CREATE_FUNC(OptionsLayer);
	};
}

#endif //__OPTIONSLAYER_H__