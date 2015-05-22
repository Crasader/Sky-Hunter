#ifndef __MEDIUMENEMY_H__
#define __MEDIUMENEMY_H__

#include "BasicEnemy.h"


class MediumEnemy : public BasicEnemy
{

private:
	//virtual void behaviour(float dt);
public:
	MediumEnemy();
	CREATE_FUNC(MediumEnemy);
	virtual bool init();
};
#endif
