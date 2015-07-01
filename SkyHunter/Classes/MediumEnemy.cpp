#include "MediumEnemy.h"


Actors::MediumEnemy::MediumEnemy()
{
	ENEMY_HEALTH = 2;
	_health = ENEMY_HEALTH;
	_bulletIndex = 0;
	_initialiced = false;
	_numBullets = 10;
	setSpeed(100);
	_shootFrequencySeconds = 1.2f;
	_currentAnimation = IDLE;
	_value = 20;
	_shootFrequencySeconds = 1.0f;
}

bool Actors::MediumEnemy::init(){
	//superclass first
	if (!Sprite::init())
	{
		return false;
	}

	createBullets();
	createIdleAnimation("animacion_enemigo_B", 4);
	createExplosionAnimation("animacion_enemigo_B_explota", 6);

	//lanza la animación por defecto
	runAction(_idleAnimation);
	scheduleShoot();
	scheduleUpdate();
	setVisible(false);

	return true;
}

