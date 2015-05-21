#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include "cocos2d.h"



class Background 
{

private:
	cocos2d::Node* _parent;
	int _pos;
	bool _initialiced;
	cocos2d::Size _screen;
	cocos2d::Sprite* _bgPart1;
	cocos2d::Sprite* _bgPart2;
	std::string  _sptitePart1;
	std::string  _sptitePart2;

public:
	virtual void setParent(cocos2d::Node* parent,int pos);
	void update(float dt);
	~Background();
	void setSptite(std::string part1);

	CC_SYNTHESIZE(float, _speed, Speed);
	Background(std::string spritename);
};

#endif //__BACKGROUND_H__

