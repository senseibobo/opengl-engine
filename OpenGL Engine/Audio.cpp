#include "Audio.h"


FMOD::System* Audio::fmodSystem = nullptr;
std::unordered_map<FMOD::Channel*, std::shared_ptr<const Sound> >Audio::activeSounds;

void Audio::Initialize()
{
	FMOD_RESULT result = FMOD::System_Create(&fmodSystem);
	ERROR_CHECK(result);
	result = fmodSystem->init(512, FMOD_INIT_NORMAL, nullptr);
	ERROR_CHECK(result);
}

FMOD::Channel* Audio::PlaySound(std::shared_ptr<const Sound> sound)
{
	FMOD::Channel* channel;
	FMOD_RESULT result = fmodSystem->playSound(sound->GetSound(), nullptr, false, &channel);
	activeSounds[channel] = sound;
	ERROR_CHECK(result);
	return channel;
}

void Audio::Update()
{
	fmodSystem->update();
	std::vector<FMOD::Channel*> soundsToErase;
	for (std::pair<FMOD::Channel*, std::shared_ptr<const Sound>> pair : activeSounds)
	{
		bool isPlaying;
		pair.first->isPlaying(&isPlaying);
		if (!isPlaying)
		{
			soundsToErase.push_back(pair.first);
		}
	}
	for (FMOD::Channel* channel : soundsToErase)
	{
		auto it = activeSounds.find(channel);
		if(it != activeSounds.end())
			activeSounds.erase(it);
	}
}

void Audio::Clear()
{
	fmodSystem->close();
	fmodSystem->release();
}

FMOD::System* Audio::GetSystem()
{
	return fmodSystem;
}
