#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#define DESING_WIDTH 320
#define DESING_HEIGHT 480 

#include "cocos2d.h"

/**
@brief    Clase que lanaza la aplicacion de cocos2d 
*/
class  AppDelegate : private cocos2d::Application
{
public:
    AppDelegate();
    virtual ~AppDelegate();

    virtual void initGLContextAttrs();


	/**
	@brief  Metodo que lanza la escena que le indiquemos ademas de realizar la configuracion de pantalla
	@return true    Inicializacion correcta
	@return false   Inicializacion fallida
	*/
    virtual bool applicationDidFinishLaunching();

	/**
	@brief  Este metodo se ejecuta cuadno la aplicacion entra en background
	*/
    virtual void applicationDidEnterBackground();

	/**
	@brief  Este metodo se ejecuta cuadno la aplicacion entra en foreground
	*/
    virtual void applicationWillEnterForeground();
};

#endif // _APP_DELEGATE_H_

