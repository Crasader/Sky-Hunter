#pragma once

#include "cocos2d.h"




class Player : public cocos2d::Sprite
{
private:
	float _speed;
	struct {
		bool left;
		bool right;
		bool up;
		bool upLeft;
		bool upRight;
		bool down;
		bool downLeft;
		bool downRight;
	}controller;
	Player();
	void resetPlayerController();


	
public:
	static Player* createPlayer();
	virtual ~Player();
	void update(float dt);
	void updateTouchController(const cocos2d::Point* tapInput);
	
};

