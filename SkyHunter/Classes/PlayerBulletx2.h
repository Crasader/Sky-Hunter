
#ifndef __PLAYERBULLETx2_H__
#define __PLAYERBULLETx2_H__

#include "PlayerBullet.h"

namespace Actors{
	class PlayerBulletx2 :public PlayerBullet
	{

	public:

		CREATE_FUNC(PlayerBulletx2);
		virtual bool init();

	};
}
#endif //__PLAYERBULLETx2_H__
