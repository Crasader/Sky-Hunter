#include "TouchController.h"


USING_NS_CC;

bool TouchController::init(){
	//super first
	if (!Node::init()){
		return false;
	}

	//inicializamos el input del usuario
	_tap = Point(-1,-1);

	//inicializamos el controlodor
	resetTouchController();

	//Creamos un touchListener y le indicamos que debe hacer mediante los call back de cocos
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = std::bind(&TouchController::onTouchBegan, this, std::placeholders::_1, std::placeholders::_2);
	touchListener->onTouchMoved = CC_CALLBACK_2(TouchController::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(TouchController::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	//mediante el schedule obtenemos el mismo efecto que llamando 
	//al metodo update desde player. Aqui usaremos schedule solo para ver que
	//puede usarse en diversas situaciones, no solo en el GameLayer.
	this->schedule(schedule_selector(TouchController::update));
	return true;
}

void TouchController::update(float dt){
	resetTouchController();
	if (_tap.x<0||_tap.y<0) return;

	Point  tap = _tap;
	
	//donde esta posicionado el objeto al que se vincula el controlador
	//en este caso a la poicion del objeto player le restamos la mita de su alto y la mitad de su ancho
	//para obtener la esquina inferior izquierda
	auto originX = getParent()->getPositionX() - getParent()->getBoundingBox().size.width*0.5;
	auto originY = getParent()->getPositionY() - getParent()->getBoundingBox().size.height*0.5;

	auto playerX = originX + getParent()->getBoundingBox().size.width;
	auto playerY = originY + getParent()->getBoundingBox().size.height;

	//en fucnion de la posicion del player y de donde toque el usuario,
	//actualizamos hacia donde debe ir el sprite.
	if (tap.x > playerX && tap.y > playerY){
		_controller.upRight = true;
	}
	else if (tap.x < originX && tap.y> playerY){
		_controller.upLeft = true;
	}
	else if (tap.x > playerX && tap.y < originY){
		_controller.downRight = true;
	}
	else if (tap.x < originX && tap.y < originY){
		_controller.downLeft = true;
	}
	else if (tap.x < originX){
		_controller.left = true;
	}
	else if (tap.x > playerX){
		_controller.right = true;
	}
	else if (tap.y < originY){
		_controller.down = true;
	}
	else if (tap.y > playerY){
		_controller.up = true;
	}
	
	
}

void TouchController::resetTouchController(){
	_controller.left = false;
	_controller.right = false;
	_controller.up = false;
	_controller.upLeft = false;
	_controller.upRight = false;
	_controller.down = false;
	_controller.downLeft = false;
	_controller.downRight = false;
}


bool TouchController::onTouchBegan(Touch *touch, Event *unused_event){
	if (touch){
		_tap = touch->getLocation();
	}
	return true;
}
void TouchController::onTouchMoved(Touch *touch, Event *unused_event){
	if (touch){
		_tap = touch->getLocation();
	}
}
void TouchController::onTouchEnded(Touch *touch, Event *unused_event){
	if (touch){
		_tap = Point(-1, -1);
	}
}
