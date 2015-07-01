#ifndef __CUSTOMAUDIOENGINE_H__
#define __CUSTOMAUDIOENGINE_H__
#include <string>
namespace Levels{
	
	/**
	@brief  esta clase es la union de CocosDenshion::SimpleAudioEngine y experimental::AudioEngine de cocos, para facilitar el desarrollo en win32
	*/
	class CustomAudioManager
	{

	private:
		CustomAudioManager();
		static CustomAudioManager* _instance;
		CustomAudioManager(CustomAudioManager const&) = delete;// copy constructor is private
		void operator=(CustomAudioManager const&) = delete;// assignment operator is private
	public:

		static CustomAudioManager* getInstance();

		/**
		@brief  metodo encargado de precargar el audio de fondo.
		@param filename la ruta del archivo de audio
		*/
		void preloadEffect(const std::string& filename);


		/**
		@brief  metodo encargado de precargar los efectos de audio.
		@param filename la ruta del archivo de audio
		*/
		void preloadBackground(const std::string& filename);


		/**
		@brief  metodo encargado de reproducir el effecto de audio.
		@param  filename la ruta del archivo de audio
		@param  loop true si debe repertirse la reproduccion, false si no
		*/
		void playEffect(const std::string& filename, bool loop);


		/**
		@brief  metodo encargado de reproducir el audio de fondo.
		@param  filename la ruta del archivo de audio
		@param  loop true si debe repertirse la reproduccion, false si no
		*/
		void playBackgroundSound(const std::string& filename, bool loop);


		/**
		@brief  pausa todos los sonidos ya sean efectos o sonidos de fondo
		*/
		void pauseAll();

		/**
		@brief  resume todos los sonidos ya sean efectos o sonidos de fondo
		*/
		void resumeAll();

		/**
		@brief  para todos los sonidos ya sean efectos o sonidos de fondo
		*/
		void stopAll();


	};
}

#endif //__CUSTOMAUDIOENGINE_H__

