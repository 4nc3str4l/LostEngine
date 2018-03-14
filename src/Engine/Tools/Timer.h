#pragma once
#include "GLFW/glfw3.h"

namespace Lost { namespace Tools {

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