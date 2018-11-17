#include "AudioManager.h"

namespace le { namespace audio {

AudioManager::AudioManager()
{
}

void AudioManager::Init()
{
	this->PlaySound();
}

std::string ErrorCheck(ALenum error)
{
	if (error == AL_INVALID_NAME)
	{
		return "\nInvalid name";
	}
	else if (error == AL_INVALID_ENUM)
	{
		return "\nInvalid enum ";
	}
	else if (error == AL_INVALID_VALUE)
	{
		return "\nInvalid value ";
	}
	else if (error == AL_INVALID_OPERATION)
	{
		return "\nInvalid operation ";
	}
	else if (error == AL_OUT_OF_MEMORY)
	{
		return "\nOut of memory like! ";
	}

	return "\nDon't know ";
}


bool isBigEndian()
{
	int a = 1;
	return !((char*)&a)[0];
}


int convertToInt(char* buffer, int len)
{
	int a = 0;
	if (!isBigEndian())
		for (int i = 0; i < len; i++)
			((char*)&a)[i] = buffer[i];
	else
		for (int i = 0; i < len; i++)
			((char*)&a)[3 - i] = buffer[i];
	return a;
}

char* loadWAV(const char* fn, int& chan, int& samplerate, int& bps, int& size)
{
	char buffer[4];
	int incrementer = 0; //for the crawler
	std::ifstream in(fn, std::ios::binary);
	in.read(buffer, 4);
	if (strncmp(buffer, "RIFF", 4) != 0)
	{
		std::cout << "this is not a valid WAVE file" << std::endl;
		return NULL;
	}
	in.read(buffer, 4);
	in.read(buffer, 4);  //WAVE
	in.read(buffer, 4);  //fmt
	in.read(buffer, 4);  //16
	in.read(buffer, 2);  //1
	in.read(buffer, 2);
	chan = convertToInt(buffer, 2);
	in.read(buffer, 4);
	samplerate = convertToInt(buffer, 4);
	in.read(buffer, 4);
	in.read(buffer, 2);
	in.read(buffer, 2);
	bps = convertToInt(buffer, 2);
	in.read(buffer, 4);  //data
	if (strncmp(buffer, "data", 4) == 0)
	{
		in.read(buffer, 4);
		size = convertToInt(buffer, 4);
		char* data = new char[size];
		in.read(data, size);
		std::cout << "\n USING DEFAULT LOADING METHOD";
		return data;
	}
	else {
		char crawler = 'F';
		bool foundD = false;
		bool foundDA = false;
		bool foundDAT = false;
		bool foundDATA = false;
		//crawl to the data
		while (!foundDATA && incrementer < 300) {
			in.read(&crawler, 1);
			if (foundDAT && crawler == 'a')
			{
				foundDATA = true;
				foundDAT = false;
				foundDA = false;
				foundD = false;
			}
			else if (foundDAT) {
				foundDATA = false;
				foundDAT = false;
				foundDA = false;
				foundD = false;
			}

			if (foundDA && crawler == 't')
			{
				foundDAT = true;
				foundDA = false;
				foundD = false;
			}
			else if (foundDA) {
				foundDATA = false;
				foundDAT = false;
				foundDA = false;
				foundD = false;
			}

			if (foundD && crawler == 'a')
			{
				foundDA = true;
				foundD = false;
			}
			else if (foundD) {
				foundDATA = false;
				foundDAT = false;
				foundDA = false;
				foundD = false;
			}
			if (crawler == 'd')
			{
				foundD = true;
			}
			incrementer++;
		}
		if (foundDATA)
		{
			std::cout << "\nFOUND DATA!!!";
			in.read(buffer, 4);
			size = convertToInt(buffer, 4);
			std::cout << "\nSize is " << size;
			char* data = new char[size];
			in.read(data, size);
			return data;
		}
		else {
			std::cout << "\nUH OH!";
			return nullptr;
		}
	}
}

ALuint loadWAVintoALBuffer(const char* fn)
{
	ALuint return_val = 0;

	int channel, sampleRate, bps, size;
	
	ALuint format = 0;
	alGenBuffers(1, &return_val);
	
	char* TONE_WAV_DATA = nullptr;
	TONE_WAV_DATA = loadWAV(fn, channel, sampleRate, bps, size);
	
	if (channel == 1)
	{
		if (bps == 8)
		{
			format = AL_FORMAT_MONO8;
		}
		else {
			format = AL_FORMAT_MONO16;
		}
	}
	else {
		if (bps == 8)
		{
			format = AL_FORMAT_STEREO8;
		}
		else {
			format = AL_FORMAT_STEREO16;
		}
	}
	alBufferData(return_val, format, TONE_WAV_DATA, size, sampleRate);

	if (TONE_WAV_DATA)
		free(TONE_WAV_DATA);
	
	return return_val;
}


void AudioManager::PlaySound()
{
	int channel, sampleRate, bps, size;
	char* data = loadWAV("S:/AuraProject_Cpp/assets/resources/music/faded.wav", channel, sampleRate, bps, size);
	
	ALCdevice* device = alcOpenDevice(NULL);
	if (device == NULL)
	{
		std::cout << "cannot open sound card" << std::endl;
		return;
	}
	
	ALCcontext* context = alcCreateContext(device, NULL);
	if (context == NULL)
	{
		std::cout << "cannot open context" << std::endl;
		return;
	}
	alcMakeContextCurrent(context);

	unsigned int bufferid, format;
	alGenBuffers(1, &bufferid);
	if (channel == 1)
	{
		if (bps == 8)
		{
			format = AL_FORMAT_MONO8;
		}
		else {
			format = AL_FORMAT_MONO16;
		}
	}
	else 
	{
		if (bps == 8)
		{
			format = AL_FORMAT_STEREO8;
		}
		else {
			format = AL_FORMAT_STEREO16;
		}
	}
	alBufferData(bufferid, format, data, size, sampleRate);
	unsigned int sourceid;
	alGenSources(1, &sourceid);
	alSourcei(sourceid, AL_BUFFER, bufferid);

	alSourcePlay(sourceid);

	//alDeleteSources(1, &sourceid);
	//alDeleteBuffers(1, &bufferid);

	//alcDestroyContext(context);
	//alcCloseDevice(device);
	delete[] data;
}

AudioManager::~AudioManager()
{
}
}}