#pragma once

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
	};
}}