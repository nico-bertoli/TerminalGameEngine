#pragma once
#include <terme/config.h>
#include <nbase_kit/singleton.h>

#include <array>
#include <SFML/Audio.hpp>

namespace terme
{
	class audio_manager : public nbase_kit::Singleton<audio_manager>
	{
		friend class nbase_kit::Singleton<audio_manager>;

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
		audio_manager();
		bool TryGetBufferAndSound(sf::SoundBuffer*& outBuffer, sf::Sound*& outSound);
	};
}