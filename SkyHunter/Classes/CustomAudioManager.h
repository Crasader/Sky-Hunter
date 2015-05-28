#ifndef __CUSTOMAUDIOENGINE_H__
#define __CUSTOMAUDIOENGINE_H__
#include <string>

class CustomAudioManager
{

private:
	CustomAudioManager();
	static CustomAudioManager* _instance;
	CustomAudioManager(CustomAudioManager const&) = delete;// copy constructor is private
	void operator=(CustomAudioManager const&) = delete;// assignment operator is private
public:
	static CustomAudioManager* getInstance();
	void preloadEffect(const std::string& filename);
	void preloadBackground(const std::string& filename);
	void playEffect(const std::string& filename, bool loop);
	void playBackgroundSound(const std::string& filename, bool loop);
	void pauseAll();
	void resumeAll();
	void stopAll();


};

#endif //__CUSTOMAUDIOENGINE_H__

