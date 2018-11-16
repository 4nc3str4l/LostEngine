#include "AudioManager.h"

namespace le { namespace audio {

AudioManager::AudioManager()
{
}

void AudioManager::Init()
{
	m_Device = alcOpenDevice(NULL);

	if (m_Device == NULL)
	{
		LOG_FAIL("Failed to initialize OpenAL");
	}

	m_Context = alcCreateContext(m_Device, NULL);

	alcMakeContextCurrent(m_Context);

	alGetError();
}

AudioManager::~AudioManager()
{
	alcDestroyContext(m_Context);
	alcCloseDevice(m_Device);
}
}}