#include "HeightEnemy.h"
#include "EnemyBulletSmart.h"



HeightEnemy::HeightEnemy()
{
	ENEMY_HEALTH = 3;
	_health = ENEMY_HEALTH;
	_bulletIndex = 0;
	_initialiced = false;
	_numBullets = 10;
	setSpeed(60);
	_shootFrequencySeconds = 1.5f;
	_currentAnimation = IDLE;
	_value = 30;
	_shootFrequencySeconds = 1.0f;
}

bool HeightEnemy::init(){
	//superclass first
	if (!Sprite::init())
	{
		return false;
	}

	createBullets();
	createIdleAnimation("jefe", 3);
	createExplosionAnimation("animacion_jefe_explota", 6);

	//start the initial animation
	runAction(_idleAnimation);
	scheduleShoot();
	scheduleUpdate();
	setVisible(false);

	return true;
}

void HeightEnemy::createBullets(){
	for (int i = 0; i < _numBullets; i++){
		_bulletPool.pushBack(EnemyBulletSmart::create());
	}
}


