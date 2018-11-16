#pragma once

#include <AL/al.h>
#include <AL/alc.h>
#include <iostream>
#include "../Tools/Log.h"


namespace le { namespace audio {
	using namespace tools;
	class AudioManager
	{
	public:
		AudioManager();
		~AudioManager();
		void Init();
	private:
		ALCcontext *m_Context;
		ALCdevice *m_Device;
	};
}}