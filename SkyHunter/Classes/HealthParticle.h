#ifndef __HEALTHPARTICLE_H__
#define __HEALTHPARTICLE_H__

#include "cocos2d.h"
namespace Actors{
	class Player;
}
namespace Components{
	class HealthParticle : public cocos2d::Node
	{
	private:
		bool _initialized;
		cocos2d::ParticleSystemQuad* _particle;
	public:
		CC_SYNTHESIZE(float, _speed, Speed);
		CC_SYNTHESIZE(Actors:: Player*, _target, Target);
		virtual void update(float dt);
		virtual void setVisible(bool visible);
		virtual bool init();
		CREATE_FUNC(HealthParticle);
	};
}

#endif //__HEALTHPARTICLE_H__

