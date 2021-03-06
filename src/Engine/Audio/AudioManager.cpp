#include "AudioManager.h"
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"

namespace le { namespace audio {

AudioManager::AudioManager()
{
}

void AudioManager::Init()
{
	this->PlaySound();
}


void AudioManager::PlaySound()
{
	
	sf::Music* music = new sf::Music();
	if (!music->openFromFile("/home/ancestral/Documents/projects/AuraProject_Cpp/build/src/resources/music/piano2.wav")) {
		LOG_FAIL("Could not load", "S:/AuraProject_Cpp/assets/resources/music/faded.wav");
	}
	// Play the music
	music->play();
	
}

AudioManager::~AudioManager()
{
}
}}