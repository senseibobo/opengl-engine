#pragma once
#include <memory>
#include "include/fmod/fmod.hpp"
class Sound : public std::enable_shared_from_this<Sound>
{
public:
	Sound()
	{
		fmodSound = nullptr;
		volume = 1.0;
	}
	//~Sound()
	//{
	//	fmodSound->release();
	//}
	static std::shared_ptr<Sound> CreateSound(const char* path);
	static std::shared_ptr<Sound> CreateSound(const char* path, float volume);
	static std::shared_ptr<Sound> CreateSound(const char* path, bool loop);
	static std::shared_ptr<Sound> CreateSound(const char* path, float volume, bool loop);

	// set
	void SetVolume(float newVolume);
	
	// get
	float GetVolume() const;
	FMOD::Sound* GetSound() const;

	// other
	FMOD::Channel* PlaySound() const;
	FMOD_RESULT LoadFile(const char* path);

private:
	FMOD::Sound* fmodSound;
	float volume;
};

