#pragma once
#include "Config.h"
#include <nbase_kit/singleton.h>

#include <array>
#include <SFML/Audio.hpp>

namespace Engine
{
	class AudioManager : public nbase_kit::Singleton<AudioManager>
	{
		friend class nbase_kit::Singleton<AudioManager>;

		//---------------------------------------------------------- Fields
	private:
		std::array<sf::Sound, 6> sounds;
		std::array<sf::SoundBuffer, 6> buffers;
		sf::Music music;
		//---------------------------------------------------------- Methods
	public:
		void PlayFx(const char* fileName, double randomPitch = 0.0);
		void PlayMusic(const char* fileName);
		void StopMusic();

	private:
		AudioManager();
		bool TryGetBufferAndSound(sf::SoundBuffer*& outBuffer, sf::Sound*& outSound);
	};
}