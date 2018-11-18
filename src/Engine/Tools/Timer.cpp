#include "Timer.h"

namespace le { namespace tools {

float Timer::DeltaTime = 0.0f;

Timer::Timer()
{
}

void Timer::Update() 
{
	DeltaTime = clock.restart().asSeconds();
}

}}