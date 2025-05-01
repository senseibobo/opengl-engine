#include "Sound.h"
#include "Audio.h"

std::shared_ptr<Sound> Sound::CreateSound(const char* path)
{
	return Sound::CreateSound(path, 1.0, false);
}

std::shared_ptr<Sound> Sound::CreateSound(const char* path, float volume)
{
	return Sound::CreateSound(path, volume, false);
}

std::shared_ptr<Sound> Sound::CreateSound(const char* path, bool loop)
{
	return Sound::CreateSound(path, 1.0, loop);
}

std::shared_ptr<Sound> Sound::CreateSound(const char* path, float volume, bool loop)
{
	std::shared_ptr<Sound> sound = std::make_shared<Sound>();

	FMOD::System* fmodSystem = Audio::GetSystem();

	FMOD_RESULT result = sound->LoadFile(path);
	ERROR_CHECK(result);
	if (loop)
	{
		sound->fmodSound->setMode(FMOD_LOOP_NORMAL);
		sound->fmodSound->setLoopCount(-1);
	}
	sound->volume = volume;

	return sound;
}

void Sound::SetVolume(float newVolume)
{
	this->volume = newVolume;
}

float Sound::GetVolume() const
{
	return this->volume;
}

FMOD::Sound* Sound::GetSound() const
{
	return this->fmodSound;
}

FMOD::Channel* Sound::PlaySound() const
{
	FMOD::Channel* channel = Audio::PlaySound(shared_from_this());
	//channel->setVolume(1.0);
	return channel;
}

FMOD_RESULT Sound::LoadFile(const char* path)
{
	FMOD_RESULT result = Audio::GetSystem()->createSound(path, FMOD_DEFAULT, nullptr, &fmodSound);
	return result;
}
