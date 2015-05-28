#ifndef __BLIZZARD_H__
#define __BLIZZARD_H__

#include "cocos2d.h"

class Blizzard : public cocos2d::Node
{
private:
	cocos2d::Size _visibleSize;
	bool _initialized;
	cocos2d::Vector<cocos2d::ParticleSystemQuad* > _snow;
	int _snowIndex;
	int _maxSnowParticles;
	void scheduleBlizzard();
	void positioningParticle();
public:
	CC_SYNTHESIZE(float, _speed, Speed);
	virtual void setParent(Node* parent);
	virtual bool init();
	virtual void update(float dt);
	CREATE_FUNC(Blizzard);
};

#endif //__BLIZZARD_H__