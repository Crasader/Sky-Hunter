
#ifndef __PLAYERBULLETx2_H__
#define __PLAYERBULLETx2_H__

#include "PlayerBullet.h"


class PlayerBulletx2 :public PlayerBullet
{

protected:
	int _damage;
public:
	
	
	//virtual void playShootSound();
	CREATE_FUNC(PlayerBulletx2);
	virtual bool init();

};
#endif //__PLAYERBULLETx2_H__
