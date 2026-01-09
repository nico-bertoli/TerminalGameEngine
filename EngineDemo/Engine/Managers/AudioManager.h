#pragma once
#include "Config.h"
#include <NbaseKit/Singleton.h>

#include <array>
#include <SFML/Audio.hpp>

namespace Engine
{
	class AudioManager : public NbaseKit::Singleton<AudioManager>
	{
		friend class NbaseKit::Singleton<AudioManager>;

		//---------------------------------------------------------- Fields
	private:
		static const size_t SOUND_SOURCES_SIZE = 6;
		std::array<sf::Sound, SOUND_SOURCES_SIZE> sounds;
		std::array<sf::SoundBuffer, SOUND_SOURCES_SIZE> buffers;
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