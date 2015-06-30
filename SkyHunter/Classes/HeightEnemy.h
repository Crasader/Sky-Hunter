

#ifndef __HEIGHTENEMY_H__
#define __HEIGHTENEMY_H__

#include "BasicEnemy.h"

namespace Actors{
	class HeightEnemy : public BasicEnemy
	{
	protected:
		virtual void createBullets();
	public:
		HeightEnemy();
		CREATE_FUNC(HeightEnemy);
		virtual bool init();



	};
}
#endif //__HEIGHTENEMY_H__