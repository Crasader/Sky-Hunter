#ifndef __ENEMYBULLETSMART_H__
#define __ENEMYBULLETSMART_H__

#include "EnemyBullet.h"

class EnemyBulletSmart : public EnemyBullet
{
private:
	cocos2d::Point _targetPosition;

public:
	CREATE_FUNC(EnemyBulletSmart);
	virtual void update(float dt);
	virtual bool init();
	virtual void setVisible(bool visitible);
	
};

#endif //__ENEMYBULLETSMART_H__