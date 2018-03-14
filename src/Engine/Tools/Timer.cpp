#include "Timer.h"

namespace Lost { namespace Tools {

float Timer::DeltaTime = 0.0f;
float Timer::lastFrame = 0.0f;

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