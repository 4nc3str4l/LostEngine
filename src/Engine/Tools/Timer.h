#pragma once
#include "GLFW/glfw3.h"

namespace LostEngine { namespace Tools {

	class Timer
	{
	public:
		Timer();
		void Update();
	public:
		float DeltaTime = 0.0f;
	private:
		float lastFrame = 0.0f;
	};
}}