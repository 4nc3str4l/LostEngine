#pragma once
#include "GLFW/glfw3.h"

namespace le { namespace tools {

	class Timer
	{
	public:
		Timer();
		void Update();
	public:
		static float DeltaTime;
	private:
		static float lastFrame;
	};
}}