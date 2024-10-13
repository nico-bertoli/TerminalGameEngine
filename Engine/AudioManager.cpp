#include "Config.h"
#include "AudioManager.h"
#include "RandomUtils.h"

AudioManager::AudioManager()
{
#if ALLOW_SOUNDS
	for (int i = 0; i < sounds.size(); ++i)
	{
		sounds[i].setBuffer(buffers[i]);
		sounds[i].stop();
	}
#endif
}

void AudioManager::PlayFx(const char* fileName, const double randomPitch)
{
#if ALLOW_SOUNDS
	Sound* sound = nullptr;
	SoundBuffer* buffer = nullptr;

	//if all sound sources are already playing, sound is not played
	if (TryGetBufferAndSound(buffer, sound) == false)
		return;

	if (!buffer->loadFromFile(fileName))
		return;

	float pitch = 1;
	if (randomPitch != 0.0)
		pitch += static_cast<float>(RandomUtils::GetRandomDouble(1.0 - randomPitch, 1.0 + randomPitch));

	sound->setPitch(pitch);
	sound->play();
#endif
}

void AudioManager::PlayMusic(const char* fileName)
{
#if ALLOW_SOUNDS
	StopMusic();
	if (music.openFromFile(fileName) == false)
		return;
	music.play();
#endif
}

bool AudioManager::TryGetBufferAndSound(SoundBuffer*& outBuffer, Sound*& outSound)
{
	for (int i = 0; i < sounds.size(); ++i)
	{
		if (sounds[i].getStatus() == SoundSource::Status::Stopped)
		{
			outBuffer = &buffers[i];
			outSound = &sounds[i];
			return true;
		}
	}
	return false;
}

void AudioManager::StopMusic()
{
#if ALLOW_SOUNDS
	if (music.getStatus() == sf::SoundSource::Playing)
		music.stop();
#endif
}
