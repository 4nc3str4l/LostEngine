#pragma once
#include "SFML/Window.hpp"

namespace le { namespace tools {

	class Timer
	{
	public:
		Timer();
		void Update();
	private:
		sf::Clock clock;
	public:
		static float DeltaTime;
	private:
		static float lastFrame;
	};
}}