#pragma once

#include <iostream>
#include <fstream>
#include <cstring>
#include <fstream>
#include <AL/al.h>
#include <AL/alc.h>
#include "../Tools/Log.h"


namespace le { namespace audio {
	using namespace tools;
	class AudioManager
	{
	public:
		AudioManager();
		~AudioManager();
		void Init();
		void PlaySound();
	private:
		ALCcontext *m_Context;
		ALCdevice *m_Device;
	};
}}