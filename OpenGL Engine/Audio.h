#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>
#include "Sound.h"
#include "include/fmod/fmod.hpp"
#include "include/fmod/fmod_errors.h"
#define ERROR_CHECK(x)		\
	do {					\
		if (x != FMOD_OK)	\
		{					\
			std::cerr << "FMOD Error: " << FMOD_ErrorString(x) << "\n"; \
		}					\
	} while (0)
class Audio
{
public:
	Audio() = delete;
	static void Initialize();
	static FMOD::Channel* PlaySound(std::shared_ptr<const Sound> sound);
	static void Update();
	static void Clear();
	static FMOD::System* GetSystem();

private:
	static FMOD::System* fmodSystem;
	static std::unordered_map<FMOD::Channel*, std::shared_ptr<const Sound>> activeSounds;
};

