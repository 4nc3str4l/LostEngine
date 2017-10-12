#include "Timer.h"

namespace LostEngine { namespace Tools {

Timer::Timer()
{
}

void Timer::Update() 
{
	float currentFrame = glfwGetTime();
	DeltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

}}