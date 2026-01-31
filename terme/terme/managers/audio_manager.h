#pragma once
#include <terme/config.h>
#include <nbkit/singleton.h>

#include <array>
#include <SFML/Audio.hpp>

namespace terme
{
	class AudioManager : public nbkit::Singleton<AudioManager>
	{
		friend class nbkit::Singleton<AudioManager>;

		//---------------------------------------------------------- fields
	private:
		std::array<sf::Sound, 6> sounds;
		std::array<sf::SoundBuffer, 6> buffers;
		sf::Music music;
		//---------------------------------------------------------- methods
	public:
		void PlayFx(const char* fileName, double randomPitch = 0.0);
		void PlayMusic(const char* fileName);
		void StopMusic();

	private:
		AudioManager();
		bool TryGetBufferAndSound(sf::SoundBuffer*& outBuffer, sf::Sound*& outSound);
	};
}