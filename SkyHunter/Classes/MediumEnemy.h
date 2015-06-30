#ifndef __MEDIUMENEMY_H__
#define __MEDIUMENEMY_H__

#include "BasicEnemy.h"

namespace Actors{
	class MediumEnemy : public BasicEnemy
	{

	public:
		MediumEnemy();
		CREATE_FUNC(MediumEnemy);
		virtual bool init();
	};
}
#endif
