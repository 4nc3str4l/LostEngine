#include "AudioManager.h"
#include <AL/al.h>
#include <AL/alc.h>
#include <iostream>



namespace le { namespace audio {

AudioManager::AudioManager()
{
}

AudioManager::~AudioManager()
{
}

void AudioManager::Init()
{
	ALCdevice *device;

	device = alcOpenDevice(NULL);
	if (!device)
		std::cout << "No audio device detected!" << std::endl;
	else
		std::cout << "Device detected!" << std::endl;

	// Way to dispose the device
	alcCloseDevice(device);
}
}}